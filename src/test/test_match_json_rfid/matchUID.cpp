#include <avr/interrupt.h>
#include "matchUID.h"
#include <ctype.h> //Ger to lower
#include <Arduino.h>


// bool matchUID(const char* a,const char* b){
	
// 	//Kollar om båda är null, returnerar false då.
// 	if (a == nullptr || b == nullptr) {
// 		return false; // Only equal if both are null
//   	}

// 	while(*a && *b){
// 		if(tolower(*a) != tolower(*b)){
// 			return false; //Ifall karaktärer ej matchar
// 		}
// 		a++;
// 		b++;
// 	}

// 	return (*a == '\0' && *b == '\0'); //Returnerar false om de har olika längd.

// }

// String convertUIDtoString(const char* a){
//   String result = ""; 
//   if(a == nullptr){
//     return result;
//   }

  
//   for(int i = 0; a[i] != '\0'; i++ ){
//     result += static_cast<char>(tolower(static_cast<unsigned char>(a[i])));
//   }

//   return result1;
// }

