#include <stdio.h>
#include <string.h>
#include "Path.h"

void Path::CreatePaths(int num){

	switch (num){
	case 0:
		id = 012;
		strcpy_s(name, 20, "Long path");
		strcpy_s(description, 200, "There is a long path with wild animals.");
		open = 1; //true
		source = 0;
		destination = 12;

	}
}