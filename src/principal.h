/*
 * principal.h
 *
 *  Created on: 30/07/2014
 *      Author: dani
 */

#ifndef PRINCIPAL_H_
#define PRINCIPAL_H_

/*Headers para OpenCl*/
#include <utility>
#define __NO_STD_VECTOR // Use cl::vector instead of STL version
#include <CL/cl.h>
/**/
#include <string>

class principal {
public:
	principal();
	virtual ~principal();
	void Platforms(cl_platform_id * platformIds);
	void DisplayPlatformInfo(cl_platform_id p,cl_platform_info name,std::string str);
	void Devices(cl_platform_id platform);
	void DisplayDevicesInfo(cl_device_id id,cl_device_info name,std::string str);
};

#endif /* PRINCIPAL_H_ */
