#include "EtherImage.h"

ModuleImage& ModuleImage::Instance()
{
	static ModuleImage* _instance = new ModuleImage();
	return *_instance;
}

ModuleImage::ModuleImage()
{

}