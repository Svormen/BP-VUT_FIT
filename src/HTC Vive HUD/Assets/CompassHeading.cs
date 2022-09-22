/*
 * Author: Slavomir Svorada
 * File: CompassHeading.cs
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System.Linq;
using System.Threading;

using System.Net;
using System;
using System.Net.Sockets;
using System.Text;

public class CompassHeading : MonoBehaviour
{
    public RawImage CompassImage;
    public RawImage CompassImageMove;
    public RawImage AngleImage;
    public RawImage middleAngle;
    public RawImage middleAnglePoint;
    public Transform Player;
    public Text CompassDirectionText;
    public RawImage airportTower;
    public RawImage CurveTest;

    // variables for data from XPLANE-11
    string headingFilePath, pitchFilePath, rollFilePath, towerFilePath;
    string getHeading, getPitch, getRoll;
    string towerHDG;

    float newAngle = 0.0f;

    // Start is called before the first frame update
    void Start()
    {
        //xplaneFileName = "Data.txt";
        headingFilePath = @"C:\GETdata\getHeading.txt";
        pitchFilePath = @"C:\GETdata\getPitch.txt";
        rollFilePath = @"C:\GETdata\getRoll.txt";
        towerFilePath = @"C:\GETdata\getTower.txt";
    }

    // Update is called once per frame
    void Update()
    {
        setHeading();
        angleMove();
    }

    // Function for Heading
    void setHeading()
    {
        getHeading = File.ReadLines(headingFilePath).Last();
        // display heading
        CompassDirectionText.text = getHeading.Substring(0, getHeading.Length - 26);

        // move compass image
        float getIntHeading;
        getIntHeading = float.Parse(getHeading);
        CurveTest.uvRect = new Rect((getIntHeading / 360), -0.01f, 1, 1);

        // airport heading location
        towerHDG = File.ReadLines(towerFilePath).Last();
        int towerHeading = int.Parse(towerHDG);
        // set tower working with compass heading
        if ((getIntHeading) < 180)
        {
            // move tower on airport heading
            if (towerHeading < 180)
            {
                airportTower.uvRect = new Rect((((towerHeading - getIntHeading) / 10) * -2.37f) - 42.02f, 0, 85, 1);
            }
            else
            {
                airportTower.uvRect = new Rect((((towerHeading - 360 - getIntHeading) / 10) * -2.37f) - 42.02f, 0, 85, 1);
            }
        }
        else
        {
            if (towerHeading < 180)
            {
                airportTower.uvRect = new Rect(((((getIntHeading - 360) - towerHeading) / 10) * 2.37f) - 42.02f, 0, 85, 1);
            }
            else
            {
                airportTower.uvRect = new Rect(((((getIntHeading - 360) - (towerHeading - 360)) / 10) * 2.37f) - 42.02f, 0, 85, 1);
            }
            // move tower on airport heading
            
        }
    }

    // Function for middle part of HUD
    void angleMove()
    {
        getRoll = File.ReadLines(rollFilePath).Last();
        float rollAngle = float.Parse(getRoll);
        if (newAngle != rollAngle)
        {
            AngleImage.transform.Rotate(new Vector3(0, 0, (rollAngle - newAngle)));
            middleAngle.transform.Rotate(new Vector3(0, 0, (rollAngle - newAngle)));
        }
        newAngle = rollAngle;

        // Pitch Middle part move
        getPitch = File.ReadLines(pitchFilePath).Last();
        float pitchAngle = float.Parse(getPitch);

        middleAngle.uvRect = new Rect(0, (pitchAngle * 0.0082f) + 0.3f, 1, 0.4f);
      
    }
}
