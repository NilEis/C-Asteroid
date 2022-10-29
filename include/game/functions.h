/**
 * @file functions.h
 * @author NilEis
 * @brief Usefull functions
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/**
 * @brief Interpolates between two values
 * 
 * @param k0 start value
 * @param k1 end value
 * @param t factor
 * @return float 
 */
float lerp(float k0, float k1, float t);

/**
 * @brief Interpolates between two values (more precise but 'slower')
 * 
 * @param k0 start value
 * @param k1 end value
 * @param t factor
 * @return float 
 */
float lerp_precise(int k0, int k1, float t);

#endif // FUNCTIONS_H
