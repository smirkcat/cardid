#include "tojava.h"
#include "mser.h"
#include "headline.h"

JNIEXPORT jbyteArray JNICALL Java_com_ocr_jni_Mser_detectIdNum
(JNIEnv *env, jobject obj, jbyteArray image){
	jboolean isCopy = JNI_FALSE;
	int size = env->GetArrayLength(image);
	jbyte* imagebuffer = env->GetByteArrayElements(image, &isCopy);
	if (NULL == imagebuffer)
	{
		return NULL;
	}
	vector<uchar> outputdata;
	Mser fun;
	Mat src = imdecode(Mat(1, size, CV_8U, imagebuffer), IMREAD_COLOR);
	Mat dst = fun.detectNumber(src);

	if (!dst.data)
		return NULL;

	env->ReleaseByteArrayElements(image, imagebuffer, 0);
	imencode(".bmp", dst, outputdata);

	jbyteArray outarray = env->NewByteArray(outputdata.size());
	env->SetByteArrayRegion(outarray, 0, outputdata.size(), (jbyte*)&outputdata[0]);

	return outarray;
}