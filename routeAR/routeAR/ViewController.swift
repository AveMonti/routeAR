//
//  ViewController.swift
//  routeAR
//
//  Created by Mateusz Chojnacki on 3/22/18.
//  Copyright © 2018 Mateusz Chojnacki. All rights reserved.
//

import UIKit
import TomTomOnlineSDKRouting
import ARKit
import SceneKit
import CoreLocation
class ViewController: UIViewController,ARSCNViewDelegate, CLLocationManagerDelegate,ARLocationDelegae,TTRouteResponseDelegate {
    @IBOutlet weak var arView: ARSCNView!
    @IBOutlet weak var addBTN: UIButton!
    
    //AR + Location
    var userLocation = CLLocation()
    var arLocationManager = ARLocation()
    let locationManager = CLLocationManager()
    //Route
    var routePlaner:TTRoute = TTRoute()
    var query:TTRouteQuery = TTRouteQuery()
    
    func addChildNode(modelNode: SCNNode!) {
        self.arView.scene.rootNode.addChildNode(modelNode)
    }
    
    func route(_ route: TTRoute!, completedWith result: TTRouteResult!) {
        
        for route in result.routes{
            for leg in route.legs{
                for coordinate in leg.elements{
                 
                    let coreLocation = CLLocationCoordinate2DMake(CLLocationDegrees(coordinate.cgVectorValue.dx), CLLocationDegrees(coordinate.cgVectorValue.dy))
                    self.arLocationManager.updatePin(userLocation: userLocation, pinLocaton: coreLocation)
                }
            }
        }
    }
    
    func route(_ route: TTRoute!, completedWith responseError: TTResponseError!) {
        
    }
    

    override func viewDidLoad() {
        super.viewDidLoad()
        // Route
        self.routePlaner.delegate = self
        //
        self.arLocationManager.delegate = self
        self.arView.delegate = self
        let scene = SCNScene()
        
        // Set the scene to the view
        self.arView.scene = scene
        
        // Start location services
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBest
        locationManager.requestWhenInUseAuthorization()
        //BTN
        self.addBTN.tintColor = UIColor.darkGray
        
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        // Create a session configuration
        let configuration = ARWorldTrackingConfiguration()
        configuration.worldAlignment = .gravityAndHeading
        
        // Run the view's session
        self.arView.session.run(configuration)
    }
    
    // Location
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print(error.localizedDescription)
    }
    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
        if status == .authorizedWhenInUse {
            self.locationManager.requestLocation()
        }
    }
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        if let location = locations.last {
            userLocation = location
            self.addBTN.tintColor = UIColor.yellow
            
        }
    }
    
    @IBAction func AddRoute(_ sender: Any) {
        self.routePlane()
        DispatchQueue.main.asyncAfter(deadline: .now() + 10) { // change 2 to desired number of seconds
            self.drowLine()
        }
    }
    
    func routePlane(){
        let routeType = TTOptionTypeRoute.shortest
//        self.query = TTRouteQueryBuilder(dest: CLLocationCoordinate2DMake(52.404745, 19.743843), withOrig: CLLocationCoordinate2DMake(userLocation.coordinate.latitude, userLocation.coordinate.longitude)).withRouteType(routeType).build()
        self.query = TTRouteQueryBuilder(dest: CLLocationCoordinate2DMake(52.402820, 19.741043), withOrig: CLLocationCoordinate2DMake(52.403347, 19.741853)).withRouteType(routeType).build()
        
        
        self.routePlaner.plan(self.query)
    }
    
    func drowLine(){
        let mat = SCNMaterial()
        mat.diffuse.contents  = UIColor.yellow
        mat.specular.contents = UIColor.green
        
        let count = self.arView.scene.rootNode.childNodes.count
        for i in 0..<count-1{
            let lineNode = LineNode(v1:arView.scene.rootNode.childNodes[i].position , v2: arView.scene.rootNode.childNodes[i+1].position, material: [mat])
            
            self.arView.scene.rootNode.addChildNode(lineNode)
        }
    }

    
}



