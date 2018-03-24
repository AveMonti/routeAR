//
//  ARLocation.swift
//  arTest
//
//  Created by Mateusz Chojnacki on 07.03.2018.
//  Copyright © 2018 Mateusz Chojnacki. All rights reserved.
//

import Foundation
import SceneKit
import CoreLocation


protocol ARLocationDelegae {
    func addChildNode(modelNode: SCNNode!)
}

class ARLocation{
    
    var delegate: ARLocationDelegae? = nil
    // AR stuff
    var modelNode:SCNNode!
    var arrayModel:NSMutableArray = NSMutableArray();
    let rootNodeName = "cube"
    var originalTransform:SCNMatrix4!
    var distance : Float! = 0.0
    var heading : Double! = 0.0
    var userLocation = CLLocation()
    
    func updatePin(userLocation: CLLocation, pinLocaton :CLLocationCoordinate2D){
        
        self.userLocation = userLocation
        let heading = 10.0
        
        self.heading = heading
        self.updateLocation(pinLocaton.latitude, pinLocaton.longitude)
    }
    
    func updateLocation(_ latitude : Double, _ longitude : Double) {
        let location = CLLocation(latitude: latitude, longitude: longitude)
        self.distance = Float(location.distance(from: userLocation))
        
        
        let modelScene = SCNScene(named: "art.scnassets/cube.dae")!
        self.modelNode = modelScene.rootNode.childNode(withName: rootNodeName, recursively: true)!
        // Move model's pivot to its center in the Y axis
        let (minBox, maxBox) = self.modelNode.boundingBox
        self.modelNode.pivot = SCNMatrix4MakeTranslation(0, (maxBox.y - minBox.y)/2, 0)
        
        // Save original transform to calculate future rotations
        self.originalTransform = self.modelNode.transform
        
        // Position the model in the correct place
        positionModel(location)
        
        // Add the model to the scene
        
        let newNode = self.modelNode
        
        if delegate != nil{
            delegate?.addChildNode(modelNode: newNode)
        }
    }
    
    func rotateNode(_ angleInRadians: Float, _ transform: SCNMatrix4) -> SCNMatrix4 {
        let rotation = SCNMatrix4MakeRotation(angleInRadians, 0, 1, 0)
        return SCNMatrix4Mult(transform, rotation)
    }
    
    func positionModel(_ location: CLLocation) {
        // Rotate node
        self.modelNode.transform = rotateNode(Float(-1 * (self.heading - 180).toRadians()), self.originalTransform)
        
        // Translate node
        self.modelNode.position = translateNode(location)
        
        // Scale node
        self.modelNode.scale = scaleNode(location)
    }
    
    func translateNode (_ location: CLLocation) -> SCNVector3 {
        let locationTransform = transformMatrix(matrix_identity_float4x4, userLocation, location)
        return positionFromTransform(locationTransform)
    }
    
    func scaleNode (_ location: CLLocation) -> SCNVector3 {
        let scale = max( min( Float(1000/distance), 1.5 ), 3 )
        return SCNVector3(x: scale, y: scale, z: scale)
    }
    
    func positionFromTransform(_ transform: simd_float4x4) -> SCNVector3 {
        return SCNVector3Make(transform.columns.3.x, transform.columns.3.y, transform.columns.3.z)
    }
    
    func transformMatrix(_ matrix: simd_float4x4, _ originLocation: CLLocation, _ driverLocation: CLLocation) -> simd_float4x4 {
        let bearing = bearingBetweenLocations(userLocation, driverLocation)
        let rotationMatrix = rotateAroundY(matrix_identity_float4x4, Float(bearing))
        
        let position = vector_float4(0.0, 0.0, -distance, 0.0)
        let translationMatrix = getTranslationMatrix(matrix_identity_float4x4, position)
        
        let transformMatrix = simd_mul(rotationMatrix, translationMatrix)
        
        return simd_mul(matrix, transformMatrix)
    }
    
    func rotateAroundY(_ matrix: simd_float4x4, _ degrees: Float) -> simd_float4x4 {
        var matrix = matrix
        
        matrix.columns.0.x = cos(degrees)
        matrix.columns.0.z = -sin(degrees)
        
        matrix.columns.2.x = sin(degrees)
        matrix.columns.2.z = cos(degrees)
        return matrix.inverse
    }
    
    func getTranslationMatrix(_ matrix: simd_float4x4, _ translation : vector_float4) -> simd_float4x4 {
        var matrix = matrix
        matrix.columns.3 = translation
        return matrix
    }
    
    func bearingBetweenLocations(_ originLocation: CLLocation, _ driverLocation: CLLocation) -> Double {
        let lat1 = originLocation.coordinate.latitude.toRadians()
        let lon1 = originLocation.coordinate.longitude.toRadians()
        
        let lat2 = driverLocation.coordinate.latitude.toRadians()
        let lon2 = driverLocation.coordinate.longitude.toRadians()
        
        let longitudeDiff = lon2 - lon1
        
        let y = sin(longitudeDiff) * cos(lat2);
        let x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(longitudeDiff);
        
        return atan2(y, x)
    }
    
}

