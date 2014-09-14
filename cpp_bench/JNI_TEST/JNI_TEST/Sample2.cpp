#include <jni.h>
#include <string.h>
#include <stdio.h>

// 环境变量PATH在windows下和linux下的分割符定义
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif


int main(void)
{
	JavaVMOption options[3];
	JNIEnv *env;
	JavaVM *jvm;
	JavaVMInitArgs vm_args;
	
	long status;
	jclass cls;
	jmethodID mid;
	jfieldID fid;
	jobject obj;
	
	options[0].optionString = "-Djava.compiler = NONE";
	options[1].optionString = "-Djava.class.path=.;D:/Universal_Tank/apache-jena-2.12.0/lib/commons-codec-1.6.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/httpclient-4.2.6.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/httpclient-cache-4.2.6.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/httpcore-4.2.5.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jackson-annotations-2.3.0.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jackson-core-2.3.3.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jackson-databind-2.3.3.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jcl-over-slf4j-1.7.6.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jena-arq-2.12.0.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jena-core-2.12.0.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jena-iri-1.1.0.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jena-sdb-1.5.0.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jena-tdb-1.1.0.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/jsonld-java-0.5.0.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/log4j-1.2.17.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/slf4j-api-1.7.6.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/slf4j-log4j12-1.7.6.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/xercesImpl-2.11.0.jar;D:/Universal_Tank/apache-jena-2.12.0/lib/xml-apis-1.4.01.jar;";
	options[2].optionString = "-verbose:NONE";
	memset(&vm_args, 0, sizeof(vm_args));
	vm_args.version = JNI_VERSION_1_4;
	vm_args.nOptions = 3;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = JNI_TRUE;
	
	// 启动虚拟机
	status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	
	if (status != JNI_ERR)
	{
		
		// 先获得class对象
		cls = env->FindClass("Sample2");
		if (cls != 0)
		{
			
			// 获取方法ID, 通过方法名和签名, 调用静态方法
			mid = env->GetStaticMethodID(cls, "sayHello", "(Ljava/lang/String;)Ljava/lang/String;");
			if (mid != 0)
			{

				const char* name = "World33";
				jstring arg = env->NewStringUTF(name);
				jstring result = (jstring)env->CallStaticObjectMethod(cls, mid, arg);
				const char* str = env->GetStringUTFChars(result, false);
				printf("Result of sayHello: %s\n", str);
				env->ReleaseStringUTFChars(result, 0);
				
				//const char* name = "World22";
				//jstring arg = env->NewStringUTF(name);
				//jstring result = (jstring)env->CallStaticObjectMethod(cls, mid, arg);
				////long result = (jlong)env->CallStaticObjectMethod(cls, mid, arg);


				////somthing wrong with the following three lines
				//const char* str = env->GetStringUTFChars(result, 0);printf("here");
				////printf("Result of sayHello: %s\n",str);
				////env->ReleaseStringUTFChars(result, 0);
				
			}
			
			/*** 新建一个对象 ***/
			// 调用默认构造函数
			//obj = env->AllocObjdect(cls); 
			
			// 调用指定的构造函数, 构造函数的名字叫做<init>
			mid = env->GetMethodID(cls, "<init>", "()V");
			obj = env->NewObject(cls, mid);
			if (obj == 0)
			{
				printf("Create object failed!\n");
			}
			/*** 新建一个对象 ***/
			
			// 获取属性ID, 通过属性名和签名
			fid = env->GetFieldID(cls, "name", "Ljava/lang/String;");
			if (fid != 0)
			{
				const char* name = "icejoywoo";
				jstring arg = env->NewStringUTF(name);
				env->SetObjectField(obj, fid, arg); // 修改属性
			}
			
			// 调用成员方法
			mid = env->GetMethodID(cls, "sayHello", "()Ljava/lang/String;");
			if (mid != 0)
			{
				jstring result = (jstring)env->CallObjectMethod(obj, mid);
				printf("here");
				const char* str = env->GetStringUTFChars(result, false);
				printf("Result of sayHello: %s\n", str);
				env->ReleaseStringUTFChars(result, 0);
			}
		}
		
		jvm->DestroyJavaVM();
		return 0;
	}
	else
	{
		printf("JVM Created failed!\n");
		return -1;
	}
}