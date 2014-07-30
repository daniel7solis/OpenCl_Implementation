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

principal::principal() {
	// TODO Auto-generated constructor stub

}

principal::~principal() {
	// TODO Auto-generated destructor stub
}

int main(){
	cl_int errNum;
	cl_uint numPlatforms;
	cl_platform_id * platformIds;
	cl_context context = NULL;

	/*Función que si se pasa como NULL el segundo parametro, retorna la cantidad
	 * de Plataformas disponibles; los argumentos son:
	 * clGetPlatformIDs(cl_uint num_entries,cl_platform_id * platforms,cl_uint * num_platforms)
	 * Una plataforma es un perfil que describe las caracteristicas
	 * y capacidades de la version particular dela version de OpenCl
	 * soportada*/
	errNum = clGetPlatformIDs(0, NULL, &numPlatforms);
	cout <<"Numero de plataformas en tu equipo: "<< numPlatforms << endl;
	platformIds = (cl_platform_id *)alloca(sizeof(cl_platform_id) * numPlatforms);

	errNum = clGetPlatformIDs(numPlatforms, platformIds, NULL);

	/*Obtener infomación de las plataformas*/
	cl_int err;
	size_t size;
	err = clGetPlatformInfo(platformIds[0], CL_PLATFORM_NAME, 0, NULL, &size);
	char * name = (char *)alloca(sizeof(char) * size);
	err = clGetPlatformInfo(platformIds[0], CL_PLATFORM_NAME, size, name, NULL);
	err = clGetPlatformInfo(platformIds[0], CL_PLATFORM_VENDOR, 0, NULL, &size);
	char * vname = (char *)alloca(sizeof(char) * size);
	err = clGetPlatformInfo(platformIds[0], CL_PLATFORM_VENDOR, size, vname, NULL);
	std::cout << "Platform name: " << name << std::endl
			  << "Vendor name : " << vname << std::endl;

	return 0;
}
