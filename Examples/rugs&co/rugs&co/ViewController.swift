//
//  ViewController.swift
//  rugs&co RoomScan API Demo app
//
//  Created by Locometric Ltd on 01/11/2024.
//

import UIKit
import RoomScanAPI

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }
    
    func getDocumentsDirectory() -> URL {
        let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
        let documentsDirectory = paths[0]
        return documentsDirectory
    }
    
    let shared = Helper.sharedInstance()

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        shared.setAccentColour(.green)

        // create or load a property from our documents directory
        let url = getDocumentsDirectory().appendingPathComponent("property.rugsfile")
        if FileManager.default.fileExists(atPath: url.path) {
            shared.setProperty(url)
        } else {
            shared.createProperty(at: url)
        }
    }
    
    @IBAction func openRoomList(_ sender: Any) {
        let roomListViewController = shared.roomListViewController()
        self.navigationController!.pushViewController(roomListViewController, animated: true)
    }
    
    @IBAction func createMyRoom(_ sender: Any) {
        let newRoomViewController = shared.newRoomViewController(withRoomName: "My Room", floor: "Ground Floor", roomType: .room)
        self.navigationController!.pushViewController(newRoomViewController, animated: true)
    }
    
    @IBAction func createAnotherRoom(_ sender: Any) {
        let newRoomViewController = shared.newRoomViewController(withRoomName: "Another Room", floor: "Ground Floor", roomType: .room)
        self.navigationController!.pushViewController(newRoomViewController, animated: true)
        DispatchQueue.main.async {
            self.shared.startScan(newRoomViewController, preferredMethod: .brickMode)
        }
    }
    
    @IBAction func plotScan(_ sender: Any) {
        let newRoomViewController = shared.newRoomViewController(withRoomName: "Plot Scan", floor: "Outside", roomType: .plot)
        self.navigationController!.pushViewController(newRoomViewController, animated: true)
    }
    
    @IBAction func exteriorScan(_ sender: Any) {
        let newRoomViewController = shared.newRoomViewController(withRoomName: "Exterior Scan", floor: "Outside", roomType: .exterior)
        self.navigationController!.pushViewController(newRoomViewController, animated: true)
    }
    
    @IBAction func exportAsPDF(_ sender: Any) {
        let property = shared.property()
        property?.export(as: .pdf, completion: { data, message in
            if let message {
                let alert = UIAlertController(title: "Export Message", message: message, preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default))
                self.present(alert, animated: true)
            }
            
            if let data {
                let outputURL = self.getDocumentsDirectory().appendingPathComponent("export.pdf")
                try! data.write(to: outputURL)
                let ac = UIActivityViewController(activityItems: [outputURL], applicationActivities: nil)
                ac.popoverPresentationController?.sourceView = self.navigationController?.navigationBar
                self.present(ac, animated: true)
            }
        })
    }
    
    @IBAction func exportAsESX(_ sender: Any) {
        let property = shared.property()
        property?.export(as: .xactimate, completion: { data, message in
            if let message {
                let alert = UIAlertController(title: "Export Message", message: message, preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default))
                self.present(alert, animated: true)
            }
            
            if let data {
                let outputURL = self.getDocumentsDirectory().appendingPathComponent("export.esx")
                try! data.write(to: outputURL)
                let ac = UIActivityViewController(activityItems: [outputURL], applicationActivities: nil)
                ac.popoverPresentationController?.sourceView = self.navigationController?.navigationBar
                self.present(ac, animated: true)
            }
        })
    }
}

