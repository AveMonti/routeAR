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


/**
 A TTInstruction object contains parameters with information about the actual road.
 */
@interface TTInstruction : NSObject

 /**
 Distance from the start of the route to the point of the instruction.
 */
@property (nonatomic, readonly, strong) NSNumber* routeOffsetInMeters;

/**
 Estimated travel time in seconds. Note that even when traffic=false travelTimeInSeconds still includes the delay due to traffic.
 */
@property (nonatomic, readonly, strong) NSNumber* travelTimeInSeconds;

/**
 Latitude, longitude pair.
 */
@property (nonatomic, readonly, strong) NSValue* point;

/**
 If specified, guidance instructions will be returned.
 Possible values:
 coded - returns raw instruction data without human-readable messages.
 text - returns raw instructions data with human-readable messages in plain text.
 tagged - returns raw instruction data with tagged human-readable messages to permit formatting.
 */
@property (nonatomic, readonly, strong) NSString* instructionType;


/**
 Street name of the next significant road segment after the maneuver, or of the street that should be followed.
 */
@property (nonatomic, readonly, strong) NSString* street;

 /**
 An aggregate for roadNumber elements.
 */
@property (nonatomic, readonly, strong) NSArray<NSString *> *roadNumbers;

 /**
 3-character ISO 3166-1 alpha-3 country code.
 */
@property (nonatomic, readonly, strong) NSString* countryCode;

 /**
 Text on a signpost which is most relevant to the maneuver, or to the direction that should be followed.
 */
@property (nonatomic, readonly, strong) NSString* signpostText;

/**
 Type of the junction at which the maneuver takes place.
 */
@property (nonatomic, readonly, strong) NSString* junctionType;

/**
 Indicates the direction of an instruction. If junctionType indicates a turn
 */
@property (nonatomic, readonly, strong) NSNumber* turnAngleInDecimalDegrees;

/**
 Indicates which exit to take at a roundabout.
 */
@property (nonatomic, readonly, strong) NSNumber* roundaboutExitNumber;

/**
 It is possible to optionally combine the instruction with the next one. This can be used to build messages like "Turn left and then turn right".
 */
@property (nonatomic, readonly) BOOL possibleCombineWithNext;

/**
 Indicates left-hand vs. right-hand side driving at the point of the maneuver.
 */
@property (nonatomic, readonly, strong) NSString* drivingSide;

/**
 A code identifying the maneuver (e.g. 'Turn right').
 */
@property (nonatomic, readonly, strong) NSString* maneuver;

/**
 A human-readable message for the maneuver.
 */
@property (nonatomic, readonly, strong) NSString* message;

/**
 A human-readable message for the maneuver combined with the message from the next instruction.
 */
@property (nonatomic, readonly, strong) NSString* combinedMessage;

@end
