/**
 * Copyright (c) 2017 TomTom N.V. All rights reserved.
 *
 * This software is the proprietary copyright of TomTom N.V. and its subsidiaries and may be used
 * for internal evaluation purposes or commercial use strictly subject to separate licensee
 * agreement between you and TomTom. If you are the licensee, you are only permitted to use
 * this Software in accordance with the terms of your license agreement. If you are not the
 * licensee then you are not authorised to use this software in any manner and should
 * immediately return it to TomTom N.V.
 */

#import <Foundation/Foundation.h>
#import "TTInstruction.h"
#import "TTInstructionGroup.h"

/**
 A TTRouteGuidance contains parameters with instruction and group of instruction about the route.
 */
@interface TTRouteGuidance : NSObject

/**
 Return array of TTInstruction objects
 @return NSArray<TTInstruction *> *
 */
@property (nonatomic, readonly, strong) NSArray<TTInstruction *> *instructions;

/**
 Return array of TTInstructionGroup objects
 @return NSArray<TTInstructionGroup *> *
 */
@property (nonatomic, readonly, strong) NSArray<TTInstructionGroup *> *instructionGroups;

@end
