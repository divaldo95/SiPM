//
//  Parameters.cc
//  Parameters
//
//  Created by Baranyai David on 2018. 06. 30..
//  Modified for SiPM Simulation on 2018. 08. 23..
//  Copyright © 2018. Baranyai David. All rights reserved.
//

#include "SiPMParameters.hh"

SiPMParameters& SiPMParameters::GetInstance(const std::string& config_file_name)
{
    static SiPMParameters instance(config_file_name);
    instance.PrintUsedFilename();
    return instance;
}

SiPMParameters::SiPMParameters(const std::string& config_file_name) : config_file(config_file_name)
{
    ResetToDefaults();
}

SiPMParameters::~SiPMParameters()
{
}

void SiPMParameters::PrintUsedFilename()
{
    std::cout << config_file << (conf_loaded ? " loaded." : " will be loaded. Call ParseConfigFile().") << std::endl;
}

void SiPMParameters::ResetToDefaults()
{
    particleGun_position = G4ThreeVector(50, -5, 0);
    particleGun_MomentumDirection = G4ThreeVector(0.5, 1, 0);
    particleGun_energy = 1; //in GeV
    
    sipm_Dimension = G4ThreeVector(1, 1, 1); //applies to both (in cm)
    scintillator_length = 40; //the size same as sipm
    
    x_division = 10;
    y_division = 10;
    
    scint_radius = 0.25; //in cm
    
    numberofevents = 10;
}

void SiPMParameters::ParseConfigFile()
{
    std::string line;
    try
    {
        std::ifstream configfile(config_file);
        if(configfile.is_open())
        {
            while (getline(configfile, line))
            {
                std::istringstream is_line(line);
                std::string key;
                if (std::getline(is_line, key, '='))
                {
                    std::string value;
                    if(std::getline(is_line, value))
                    {
                        StoreConfigValues(key, value);
                    }
                }
            }
        }
        CheckValues();
        conf_loaded = true;
    }
    catch (char param)
    {
        std::cout << param << std::endl;
    }
}

void SiPMParameters::ParseConfigFile(std::string config_file1)
{
    config_file = config_file1;
    ParseConfigFile();
}

void SiPMParameters::StoreConfigValues(std::string key1, std::string value1)
{
    //---Particle gun position---------------------------------------------------------------------------------------------------
    if(key1.compare("pgpositionx") == 0)
    {
        particleGun_position.setX(std::stod(value1));
        std::cout << "Particle Gun X position parsed from config file! Value = " << particleGun_position.getX() << std::endl;
    }
    else if(key1.compare("pgpositiony") == 0)
    {
        particleGun_position.setY(std::stod(value1));
        std::cout << "Particle Gun Y position parsed from config file! Value = " << particleGun_position.getY() << std::endl;
    }
    else if(key1.compare("pgpositionz") == 0)
    {
        particleGun_position.setZ(std::stod(value1));
        std::cout << "Particle Gun Z position parsed from config file! Value = " << particleGun_position.getZ() << std::endl;
    }
    
    //---Particle gun momentum----------------------------------------------------------------------------------------------------
    else if(key1.compare("pgmomentumx") == 0)
    {
        particleGun_MomentumDirection.setX(std::stod(value1));
        std::cout << "Particle Gun X momentum parsed from config file! Value = " << particleGun_MomentumDirection.getX() << std::endl;
    }
    else if(key1.compare("pgmomentumy") == 0)
    {
        particleGun_MomentumDirection.setY(std::stod(value1));
        std::cout << "Particle Gun Y momentum parsed from config file! Value = " << particleGun_MomentumDirection.getY() << std::endl;
    }
    else if(key1.compare("pgmomentumz") == 0)
    {
        particleGun_MomentumDirection.setZ(std::stod(value1));
        std::cout << "Particle Gun Z momentum parsed from config file! Value = " << particleGun_MomentumDirection.getZ() << std::endl;
    }
    
    //---Particle gun energy------------------------------------------------------------------------------------------------------
    else if(key1.compare("pgenergy") == 0)
    {
        particleGun_energy = std::stod(value1);
        std::cout << "Particle Gun energy parsed from config file! Value = " << particleGun_energy << std::endl;
    }
    
    //---SiPM dimensions----------------------------------------------------------------------------------------------------------
    else if(key1.compare("sipmsizex") == 0)
    {
        sipm_Dimension.setX(std::stod(value1));
        std::cout << "SiPM X size parsed from config file! Value = " << sipm_Dimension.getX() << std::endl;
    }
    else if(key1.compare("sipmsizey") == 0)
    {
        sipm_Dimension.setY(std::stod(value1));
        std::cout << "SiPM Y size parsed from config file! Value = " << sipm_Dimension.getY() << std::endl;
    }
    else if(key1.compare("sipmsizez") == 0)
    {
        sipm_Dimension.setZ(std::stod(value1));
        std::cout << "SiPM Z size parsed from config file! Value = " << sipm_Dimension.getZ() << std::endl;
    }
    
    //---Sscintillator------------------------------------------------------------------------------------------------------------
    else if(key1.compare("scintillatorlength") == 0)
    {
        scintillator_length = std::stod(value1);
        scintillator_Dimension.setZ(std::stod(value1));
        std::cout << "Scintillator length parsed from config file! Value = " << scintillator_length << std::endl;
    }
    else if(key1.compare("scintillatorradius") == 0)
    {
        scint_radius = std::stod(value1);
        std::cout << "Scintillator radius parsed from config file! Value = " << scint_radius << std::endl;
    }
    
    //---Sscintillator------------------------------------------------------------------------------------------------------------
    else if(key1.compare("xdivision") == 0)
    {
        x_division = std::stod(value1);
        std::cout << "X division parsed from config file! Value = " << x_division << std::endl;
    }
    else if(key1.compare("ydivision") == 0)
    {
        y_division = std::stod(value1);
        std::cout << "Y division parsed from config file! Value = " << y_division << std::endl;
    }


    else if (key1.compare("scintillatorsizex") == 0)
    {
        scintillator_Dimension.setX(std::stod(value1));
        std::cout << "Scintillator X size set from config file! Value = " << scintillator_Dimension.getX() << std::endl;
    }
    else if (key1.compare("scintillatorsizey") == 0)
    {
        scintillator_Dimension.setY(std::stod(value1));
        std::cout << "Scintillator Y size set from config file! Value = " << scintillator_Dimension.getY() << std::endl;
    }
    else if (key1.compare("scintillatorsizez") == 0)
    {
        scintillator_Dimension.setZ(std::stod(value1));
        std::cout << "Scintillator Z size set from config file! Value = " << scintillator_Dimension.getZ() << std::endl;
    }

    else if (key1.compare("scintillatorisbox") == 0)
    {
        if (std::stod(value1) != 0)
        {
            scintIsBox = true;
            std::cout << "Using box scintillator." << std::endl;
        }
        else
        {
            scintIsBox = false;
            std::cout << "Using tube scintillator." << std::endl;
        }
    }

    else if (key1.compare("firstsipmenabled") == 0)
    {
        if (std::stod(value1) != 0)
        {
            sipm1Enabled = true;
            std::cout << "First SiPM enabled." << std::endl;
        }
        else
        {
            sipm1Enabled = false;
            std::cout << "First SiPM disabled." << std::endl;
        }
    }

    else if (key1.compare("secondsipmenabled") == 0)
    {
        if (std::stod(value1) != 0)
        {
            sipm2Enabled = true;
            std::cout << "Second SiPM enabled." << std::endl;
        }
        else
        {
            sipm2Enabled = false;
            std::cout << "Second SiPM disabled." << std::endl;
        }
    }

    else if (key1.compare("coatingthickness") == 0)
    {
        cThickness = std::stod(value1);
        std::cout << "Coating thickness set to " << cThickness << std::endl;
    }

    else if (key1.compare("lengthunit") == 0)
    {
        if (value1.compare("mm") == 0)
        {
            std::cout << "Length unit is mm." << std::endl;
            globalLengthUnit = mm;
        }
        else if (value1.compare("cm") == 0)
        {
            std::cout << "Length unit is cm." << std::endl;
            globalLengthUnit = cm;
        }
        else if (value1.compare("m") == 0)
        {
            std::cout << "Length unit is m." << std::endl;
            globalLengthUnit = m;
        }
    }
    
    //---Number of events---------------------------------------------------------------------------------------------------------
    else if(key1.compare("numberofevents") == 0)
    {
        numberofevents = std::stod(value1);
        std::cout << "Number of events parsed from config file! Value = " << numberofevents << std::endl;
    }
}

void SiPMParameters::CheckValues()
{
    if(x_division <= 0)
    {
        std::cout << "X division is at least 1, setting back the default value." << std::endl;
        x_division = 1;
    }
    if(y_division <= 0)
    {
        std::cout << "Y division is at least 1, setting back the default value." << std::endl;
        y_division = 1;
    }
    if(scint_radius*2 > sipm_Dimension.getX() || scint_radius*2 > sipm_Dimension.getY())
    {
        std::cout << "Scintillator diameter can not be larger than the SiPM, ";
        if(sipm_Dimension.getX() < sipm_Dimension.getY())
        {
            scint_radius = sipm_Dimension.getX() / 2;
            std::cout << "changed to " << scint_radius * 2 << std::endl;
        }
        else
        {
            scint_radius = sipm_Dimension.getY() / 2;
            std::cout << "changed to " << scint_radius * 2 << std::endl;
        }
    }
}
