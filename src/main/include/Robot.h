/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <networktables/NetworkTableEntry.h>
#include <rev/CANSparkMax.h>

#include "lib/CSVLogFile.h"

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

private:
  frc::XboxController m_DriverController{0};
  nt::NetworkTableEntry m_IsEnabledEntry, m_PowerEntry, m_LogEntry, m_LogFilename;
  CSVLogFile *m_LogFile;

  rev::CANSparkMax m_RightMotor{7, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANSparkMax m_LeftMotor{6, rev::CANSparkMax::MotorType::kBrushless};
  rev::CANEncoder m_RightEncoder{m_RightMotor};
  rev::CANEncoder m_LeftEncoder{m_LeftMotor};

  bool m_ShooterEnabled;
};
