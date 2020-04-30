#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <string.h>

static char* errorCodeToString(jint e);
int execute(int argc,char** argv,char* className){
	int returnValue=EXIT_SUCCESS;
	JavaVM *jvm=malloc(sizeof(struct JNIInvokeInterface_));
	JNIEnv *env=malloc(sizeof(struct JNINativeInterface_));
	JavaVMInitArgs vm_args;
	JavaVMOption * options=calloc(2,sizeof(struct JavaVMOption));
	if(options==NULL){
		fputs("Out of memory!",stderr);
		return EXIT_FAILURE;
	}
	size_t lenClasspath=strlen("-Djava.class.path=");
	size_t lenEnvironmentVariable=strlen(getenv("CLASSPATH"));
	options[0].optionString=calloc(lenClasspath+lenEnvironmentVariable+1,1);//+1 for the null terminator
	if(options[0].optionString==NULL){
		fputs("Out of memory!",stderr);
		return EXIT_FAILURE;
	}
	sprintf(options[0].optionString,"%s%s","-Djava.class.path=",getenv("CLASSPATH"));
	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions = 1;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = 0;
	jint returnValueOfJVMCreation=JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
	if(returnValueOfJVMCreation!=JNI_OK){
		fputs("An error occurred while creating the JVM!",stderr);
		fprintf(stderr,"Errorcode: %s\n",errorCodeToString(returnValueOfJVMCreation));
		return EXIT_FAILURE;
	}
	jclass jasmClass=(*env)->FindClass(env,className);
	if(jasmClass==NULL){
		fprintf(stderr,"Couldn't find class %s\n",className);
		returnValue=EXIT_FAILURE;
		goto cleanup;
	}
	jmethodID mainMethodID=(*env)->GetStaticMethodID(env,jasmClass,"main","([Ljava/lang/String;)V");
	if(jasmClass==NULL){
		fprintf(stderr,"Couldn't find method main ([Ljava/lang/String;)V in %s\n",className);
		returnValue=EXIT_FAILURE;
		goto cleanup;
	}
	jclass stringClass=(*env)->FindClass(env,"java/lang/String");
	if(stringClass==NULL){
		fputs("Couldn't find class java/lang/String\n",stderr);
		returnValue=EXIT_FAILURE;
		goto cleanup;
	}
	jobjectArray args=(*env)->NewObjectArray(env,argc,stringClass,NULL);
	for(int i=0;i<argc;i++){
		jstring arg=(*env)->NewStringUTF(env,argv[i]);
		(*env)->SetObjectArrayElement(env,args,i,arg);
	}
	(*env)->CallStaticVoidMethod(env,jasmClass,mainMethodID,args);
	
	cleanup:
	{//TODO. This is ugly.
		jint returnValueOfJVMDestruction=(*jvm)->DestroyJavaVM(jvm);
		if(returnValueOfJVMDestruction!=JNI_OK){
			fputs("An error occurred while destroying the JVM!",stderr);
			fprintf(stderr,"Errorcode: %s\n",errorCodeToString(returnValueOfJVMDestruction));
		}
	}
	return returnValue;
}
static char* errorCodeToString(jint e){
	switch(e){
		case JNI_OK:return "JNI_OK";
		case JNI_ERR:return "JNI_ERR";
		case JNI_EDETACHED:return "JNI_EDETACHED";
		case JNI_EVERSION:return "JNI_EVERSION";
		case JNI_ENOMEM:return "JNI_ENOMEM";
		case JNI_EEXIST:return "JNI_EEXIST";
		case JNI_EINVAL:return "JNI_EINVAL";
	}
	return "(Unknown error)";
}
