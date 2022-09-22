/*
 * Author: Slavomir Svorada
 * File: FileManager.cs
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using UnityEngine.UI;
using System.Linq;
using UnityEditor;
using System.Threading;

public class FileManager : MonoBehaviour
{
    [SerializeField] Text txt_allNumbers, txt_randomNumber, qnh_number, enginePerformanceLeft, enginePerformanceRight, enginePerformanceLeft2, enginePerformanceRight2, AirSpeed, GroudSpeed, A_number, M_number, G_number, Altitude;

    public RawImage altitudeImage;
    string[] numbersArray, speeds, leftEng, rightEng;
    string myFilePath, lastNumber, getAirspeed, myFilePath2, myFilePath3, myFilePath4, getGroundspeed, getAltitude, myFilePath5, getMach, getG, getA, myFilePath6, myFilePath7;
    int leftEngine, rightEngine, leftEngine2, rightEngine2;
    string speedFilename, speedMyFilePath, speedLast, allE;
    string resultValue, resultEng;

    // xplane variables
    string xplaneFileName, xplaneFilePath;

    // Start is called before the first frame update
    void Start()
    {
        //myFilePath = Application.dataPath + "/" + filename;
        myFilePath = @"C:\GETdata\getAirspeed.txt";
        myFilePath2 = @"C:\GETdata\getGroundspeed.txt";
        myFilePath3 = @"C:\GETdata\getQnh.txt";
        myFilePath4 = @"C:\GETdata\getAltitude.txt";
        myFilePath5 = @"C:\GETdata\getMach.txt";
        myFilePath6 = @"C:\GETdata\getGload.txt";
        myFilePath7 = @"C:\GETdata\getEngine.txt";
    }

    void Update()
    {
        // method getting data from 'test.txt' file for QNH testing
        DisplayQnhNumber();
        setAirspeed();
        setGroundSpeed();
        setAltitude();
        leftDataBlock();
        // method for checking engined stabilization
        enginePerformance();
    }

    void DisplayQnhNumber()
    {
        //AssetDatabase.Refresh();
        lastNumber = File.ReadLines(myFilePath3).Last();
        qnh_number.text = lastNumber;   
    }

    // Function for AirSpeed
    void setAirspeed()
    {
        getAirspeed = File.ReadLines(myFilePath).Last();
        AirSpeed.text = getAirspeed;
    }

    // Function for GroundSpeed
    void setGroundSpeed()
    {
        getGroundspeed = File.ReadLines(myFilePath2).Last();
        GroudSpeed.text = getGroundspeed;
    }

    // Function for Altitude
    void setAltitude()
    {
        getAltitude = File.ReadLines(myFilePath4).Last();
   
        Altitude.text = getAltitude.Substring(0, getAltitude.Length - 28);
        
        string cutString = getAltitude.Substring(getAltitude.Length - 28);
        float getCutAltitude = float.Parse(cutString);

        altitudeImage.uvRect = new Rect(0,  (((getCutAltitude) * 0.01f ) + 0.24f), 1, 0.53f);

    }

    // method for engine thrust
    void enginePerformance()
    {
        char[] separators = new char[] { '|', ' ' };

        allE = File.ReadLines(myFilePath7).Last();

        leftEng = allE.Split(separators, System.StringSplitOptions.RemoveEmptyEntries);

        // variables for engines performance
        leftEngine = int.Parse(leftEng[0]);
        rightEngine = int.Parse(leftEng[1]);
        leftEngine2 = int.Parse(leftEng[2]);
        rightEngine2 = int.Parse(leftEng[3]);

        // set color of text on demand how powerfull they are
        if ((System.Math.Abs(leftEngine - rightEngine)) != 0)
        {
            // not stabilized = 'yellow' color
            enginePerformanceLeft.color = Color.yellow;
            enginePerformanceRight.color = Color.yellow;
        }

        if ((System.Math.Abs(leftEngine2 - rightEngine2)) != 0)
        {
            // not stabilized = 'yellow' color
            enginePerformanceLeft2.color = Color.yellow;
            enginePerformanceRight2.color = Color.yellow;
        }

        enginePerformanceLeft.text = leftEng[0].ToString();
        enginePerformanceRight.text = leftEng[1].ToString();
        enginePerformanceLeft2.text = leftEng[2].ToString();
        enginePerformanceRight2.text = leftEng[3].ToString();
    }

    // method for left data block whitch are Alpha, Mach and G number
    void leftDataBlock()
    {
        // Alpha number
        /*getA = File.ReadLines(myFilePath7).Last();
        A_number.text = getA;*/

        // Mach number
        getMach = File.ReadLines(myFilePath5).Last();
        M_number.text = getMach;

        // G numberS
        getG = File.ReadLines(myFilePath6).Last();
        G_number.text = getG;
    }
}
