#pragma once

#define		SINGLETON(classType)	private:\
										classType();\
										~classType();\
										friend class CSingleton<classType>;