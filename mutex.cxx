//MutexLock和MutexLockGuard这两个类不允许拷贝构造和赋值
class MutexLock : boost::noncopyable {
    public:
        MutexLock() : holder_(0) {
            pthread_mutex_init(&mutex_, NULL);
        }

        ~MutexLock() {
            assert(holder_ == 0);
            pthread_mutex_destory(&mutex_);
        }

        bool isLockedByThisThread() {
            return (holder_ == CurrentThread::tid());
        }

        void assertLocked() {
            assert(isLockedByThisThread());
        }

        void lock() {   //仅供MutexLockGuard调用，严禁用户代码调用
            pthread_mutex_lock(&mutex_);
            holder_ = CurrentThread::tid();
        }

        void unlock() { //仅供MutexLockGuard调用，严禁用户代码调用
            holder_ = 0;
            pthread_mutex_unlock(&mutex_);
        }

        pthread_mutex_t* getPthreadMutex() {    //仅供condition调用，严禁用户代码调用
            return &mutex_;
        }

    private:
        pthread_mutex_t mutex_;
        pid_t holder_;
};

class MutexLockGuard : boost::noncopyable {
    public:
        explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex) {
            mutex_.lock();
        }

        ~MutexLockGuard() {
            mutex_.unlock();
        }

    private:
        MutexLock& mutex_;
} ;

class Conditon : boost::noncopyable {
    public:
        explicit Conditon(MutexLock& mutex) : mutex_(mutex) {
            pthread_cond_init(&cond_, NULL);
        }

        ~Conditon() {
            pthread_cond_destory(&cond_);
        }

        void wait() {
            pthread_cond_wait(&cond_, mutex_.getPthreadMutex());
        }

        void notify() {
            pthread_cond_signal(&cond_);
        }

        void notifyAll() {
            pthread_cond_broadcast(&cond_);
        }

    private:
        MutexLock& mutex_;
        pthread_cond_t cond_;
};