/*
 * principal.cpp
 *
 *  Created on: 30/07/2014
 *      Author: dani
 */

#include "principal.h"
/*Headers para OpenCl*/
#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#include <CL/cl.h>
/**/
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

cl_platform_id * platformIds;
cl_device_id * deviceIds;

principal::principal() {
	// TODO Auto-generated constructor stub

}

principal::~principal() {
	// TODO Auto-generated destructor stub
}

/*Función que se encarga de obtener las plataformas de OpenCl instaladas en el equipo,
 * y obtener la infoiamción*/
void principal::Platforms(cl_platform_id * platformIds){
	cl_int errNum;
	cl_uint numPlatforms;
//	cl_context context = NULL;

	/*Función que si se pasa como NULL el segundo parametro, retorna la cantidad
	 * de Plataformas disponibles; los argumentos son:
	 * clGetPlatformIDs(cl_uint num_entries,cl_platform_id * platforms,cl_uint * num_platforms)
	 * Una plataforma es un perfil que describe las caracteristicas
	 * y capacidades de la version particular dela version de OpenCl
	 * soportada*/
	// First, query the total number of platforms
	errNum = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (errNum != CL_SUCCESS || numPlatforms <= 0){
		std::cerr << "Failed to find any OpenCL platform." << std::endl;
		return;
	}

	/*Ahora creamos la locación en memoria de las plataformas
	 * que estan instaladas en el equipo*/
	// Next, allocate memory for the installed platforms, and query
	// to get the list.
	platformIds = (cl_platform_id *)alloca(sizeof(cl_platform_id) * numPlatforms);
	/*Obtenemos el Id de cada plataforma*/
	// First, query the total number of platforms
	errNum = clGetPlatformIDs(numPlatforms, platformIds, NULL);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
		return;
	}
	std::cout << "Numero de plataformas en tu equipo: \t" << numPlatforms << std::endl;

	/*Para cada plataforma en el equipo obtenemos su información*/
	// Iterate through the list of platforms displaying associated
	// information
	for (cl_uint i = 0; i < numPlatforms; i++) {
		// First we display information associated with the platform
		DisplayPlatformInfo(platformIds[i], CL_PLATFORM_NAME, "CL_PLATFORM_NAME");
		DisplayPlatformInfo(platformIds[i], CL_PLATFORM_VENDOR, "CL_PLATFORM_VENDOR");
		DisplayPlatformInfo(platformIds[i], CL_PLATFORM_PROFILE, "CL_PLATFORM_PROFILE");
		DisplayPlatformInfo(platformIds[i], CL_PLATFORM_VERSION, "CL_PLATFORM_VERSION");
		DisplayPlatformInfo(platformIds[i],	CL_PLATFORM_EXTENSIONS,"CL_PLATFORM_EXTENSIONS");
		Devices(platformIds[i]);
	}
}

/*Función que se encaraga de mostrar la información que recibe de la plataforma*/
void principal::DisplayPlatformInfo(cl_platform_id id,cl_platform_info name,std::string str){
	cl_int errNum;
	std::size_t paramValueSize;

	/*Obtiene el tamaño del parametro en la var paramValueSize*/
	errNum = clGetPlatformInfo(id,name,0,NULL,&paramValueSize);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to find OpenCL platform " << str << "." << std::endl;
		return;
	}
	/*Convierto a char lo que contiene la memoria que se obtubo en el paso anterior*/
	char * info = (char *)alloca(sizeof(char) * paramValueSize);
	/*Consulto el parametro buscado que se gurada en la misma locacion de mem*/
	errNum = clGetPlatformInfo(id,name,paramValueSize,info,NULL);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to find OpenCL platform " << str << "." << std::endl;
		return;
	}
	std::cout << "\t" << str << ":\t" << info << std::endl;
}

/*Función que obtine los devices de la plataforma*/
void principal::Devices(cl_platform_id platform){
	cl_int errNum;
	cl_uint numDevices;
	errNum = clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,0,NULL,&numDevices);
	if (numDevices < 1)
	{
		std::cout << "No GPU device found for platform "<< platform << std::endl;
//		exit(1);
	}else{
		deviceIds = (cl_device_id *)alloca(sizeof(cl_device_id) * numDevices);
		errNum = clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,numDevices,deviceIds,NULL);
	}
	std::cout << "Numero de dispositivos en la plataforma: " << numDevices << std::endl;

	/*Para cada plataforma en el equipo obtenemos su información*/
	// Iterate through the list of platforms displaying associated
	// information
	for (cl_uint i = 0; i < numDevices; i++) {
		// First we display information associated with the platform
//		DisplayDevicesInfo(deviceIds[i], CL_DEVICE_TYPE, "CL_DEVICE_TYPE");
		DisplayDevicesInfo(deviceIds[i], CL_DEVICE_MAX_COMPUTE_UNITS, "CL_DEVICE_MAX_COMPUTE_UNITS");
	}

//	errNum = clGetDeviceIDs(platform,CL_DEVICE_TYPE_CPU,0,NULL,&numDevices);
//	if (numDevices < 1)
//	{
//		std::cout << "No CPU device found for platform "<< platform << std::endl;
//		//		exit(1);
//	}else{
//		deviceIds = (cl_device_id *)alloca(sizeof(cl_platform_id) * numDevices);
//		errNum = clGetDeviceIDs(platform,CL_DEVICE_TYPE_CPU,1,deviceIds,NULL);
//	}
//	std::cout << "Numero de CPU en la plataforma: \t" << numDevices << std::endl;
//
//	/*Para cada plataforma en el equipo obtenemos su información*/
//	// Iterate through the list of platforms displaying associated
//	// information
//	for (cl_uint i = 0; i < numDevices; i++) {
//		// First we display information associated with the platform
//		//		DisplayDevicesInfo(deviceIds[i], CL_DEVICE_TYPE, "CL_DEVICE_TYPE");
////		DisplayDevicesInfo(deviceIds[i], CL_DEVICE_MAX_COMPUTE_UNITS, "CL_DEVICE_MAX_COMPUTE_UNITS");
//	}
}

//template <typename T>
void principal::DisplayDevicesInfo(cl_device_id id,cl_device_info name,std::string str){
	cl_int errNum;
	std::size_t paramValueSize;

	/*Obtiene el tamaño del parametro en la var paramValueSize*/
	errNum = clGetDeviceInfo(id,name,0,NULL,&paramValueSize);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to find OpenCL Device " << str << "." << std::endl;
		return;
	}
	/*Convierto a char lo que contiene la memoria que se obtubo en el paso anterior*/
//	T * info = (T *)alloca(sizeof(T) * paramValueSize);
//	void  info = (void )alloca(sizeof(void) * paramValueSize);
	/*Consulto el parametro buscado que se gurada en la misma locacion de mem*/
//	errNum = clGetDeviceInfo(id,name,paramValueSize,&info,NULL);
	if (errNum != CL_SUCCESS)
	{
		std::cerr << "Failed to find OpenCL Device " << str << "." << std::endl;
		return;
	}
//	std::cout << "\t" << str << ":\t" << info << std::endl;
}

int main(){
	principal p;
	p.Platforms(platformIds);
	return 0;
}
