/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>
#include <frc/shuffleboard/Shuffleboard.h>

void Robot::RobotInit()
{
    m_RightMotor.RestoreFactoryDefaults();
    m_LeftMotor.RestoreFactoryDefaults();

    m_RightMotor.SetOpenLoopRampRate(0.6);
    m_LeftMotor.SetOpenLoopRampRate(0.6);

    //m_RightMotor.EnableVoltageCompensation(11.5);
    //m_LeftMotor.EnableVoltageCompensation(11.5);

    m_LeftMotor.SetInverted(true);

    m_ShooterEnabled = false;

    m_IsEnabledEntry = frc::Shuffleboard::GetTab("Shooter").Add("Is Shooter enabled", false).WithWidget(frc::BuiltInWidgets::kBooleanBox).GetEntry();
    m_PowerEntry = frc::Shuffleboard::GetTab("Shooter").Add("Power", 0.0).WithWidget(frc::BuiltInWidgets::kNumberSlider).GetEntry();
    m_LogEntry = frc::Shuffleboard::GetTab("Shooter").Add("Logging", false).WithWidget(frc::BuiltInWidgets::kToggleButton).GetEntry();
}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit()
{
    m_ShooterEnabled = false;
    m_IsEnabledEntry.SetBoolean(m_ShooterEnabled);
}
void Robot::TeleopPeriodic()
{
    if (m_DriverController.GetAButtonPressed())
    {
        m_ShooterEnabled = !m_ShooterEnabled;
        m_IsEnabledEntry.SetBoolean(m_ShooterEnabled);
        if (m_ShooterEnabled && m_LogEntry.GetBoolean(false))
        {
            m_LogFile = new CSVLogFile("/home/lvuser/logs/log", "Power", "Right", "Left");
        }
        else
        {
            delete m_LogFile;
        }
    }

    if (m_ShooterEnabled)
    {
        double power = m_PowerEntry.GetDouble(0.0);
        m_RightMotor.Set(power);
        m_LeftMotor.Set(power);
        if (m_LogEntry.GetBoolean(false))
        {
            std::cout << power << "  " << m_RightEncoder.GetVelocity() << "  " << m_LeftEncoder.GetVelocity() << std::endl;
            m_LogFile->Log(power, m_RightEncoder.GetVelocity(), m_LeftEncoder.GetVelocity());
        }
    }
    else
    {
        m_RightMotor.StopMotor();
        m_LeftMotor.StopMotor();
    }
}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main()
{
    return frc::StartRobot<Robot>();
}
#endif
