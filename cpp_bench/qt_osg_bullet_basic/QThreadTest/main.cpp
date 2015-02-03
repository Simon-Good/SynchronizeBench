#include <QtGui>
#include <QtCore>

class Worker:public QObject
{
	Q_OBJECT
public:
	Worker(){};
public slots:
	void func(){
		qDebug()<<"test";
	}
};
//class Thread: public QThread
//{
//	Q_OBJECT
//public:
//	Thread():m_stop(false){}
//public slots:
//	void stop(){
//		qDebug()<<"Thread::stop called from main thread:"<<currentThreadId();
//		QMutexLocker locker(&m_mutex);
//		m_stop = true;
//	}
//private:
//	QMutex m_mutex;
//	bool m_stop;
//
//	void run(){
//		qDebug()<<"From worker thread:"<<currentThreadId();
//		while(1){
//			{
//				QMutexLocker locker(&m_mutex);
//				if(m_stop) break;
//			}
//			msleep(10);
//		}
//	}
//};

#include "main.moc"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qDebug()<<"From main thread:"<<QThread::currentThreadId();
	QThread t;
	Worker w;
	QTimer timer;
	QObject::connect(&timer, SIGNAL(timeout()), &w, SLOT(func()));
	timer.start(10);
	w.moveToThread(&t);
	t.start();
	return a.exec();
}
