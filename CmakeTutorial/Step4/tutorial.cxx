/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2024-12-05 21:44:44
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2024-12-13 22:31:43
 * @Description: 
 * 
 * Copyright (c) 2024 by chriswoodcn, All Rights Reserved. 
 */
// A simple program that computes the square root of a number
#include <cmath>
#include <iostream>
#include <string>

#include "MathFunctions.h"
#include "TutorialConfig.h"

int main(int argc, char* argv[])
{
  const double a = 444.4;
  
  if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

  // convert input to double
  const double inputValue = std::stod(argv[1]);

  const double outputValue = mathfunctions::sqrt(inputValue);

  std::cout << "The square root of " << inputValue << " is " << outputValue
            << std::endl;
  return 0;
}
