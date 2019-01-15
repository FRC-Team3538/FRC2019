#include "subsystem/Logging.hpp"

#include "frc/Timer.h"
#include "frc/Preferences.h"

Logging::Logging()
{
    Logging("./Logging/");
}

Logging::Logging(string path)
{
    Logging(path, "Log-#.csv");
}

Logging::Logging(string path, string _filename)
{
    // Get a log serial number from robot Preferences
    auto pref = frc::Preferences::GetInstance();
    auto logNumber = pref->GetInt("LogNumber", 1);
    auto logNumberStr = to_string(logNumber);

    // pad with zeros
    while (logNumberStr.length() < 6)
    {
        logNumberStr = "0" + logNumberStr;
    }

    // Replace # in the log file name with the log number
    auto i = _filename.find("#");
    if (i >= 0)
    {
        _filename = _filename.replace(i, logNumberStr.length(), logNumberStr);
    }

}

void Logging::AddKey(string _key)
{
    // Cannot add new columns once logging is started
    if (m_started)
        return;

    m_map[_key] = "";
}

void Logging::Start()
{
    // Cannot add new columns once logging is started
    m_started = true;

    // Lets open dat log file!
    m_file.open(m_path + m_filename);

    // Print the header
    m_file << "Time, ";

    // Print each log item
    for (auto &i : m_map)
    {
        m_file << i.first << ", ";
    }

    // Force output to disk
    m_file << endl;
    m_file.flush();
}

void Logging::Log(string _key, string _value)
{
    // Must start log first
    if (m_started)
    {
        return;
    }

    // Only update registered items
    if (m_map.count(_key) == 0)
    {
        return;
    }

    m_map[_key] = _value;
}

void Logging::Commit()
{
    // Must start log first
    if (m_started)
    {
        return;
    }

    m_file << frc::Timer::GetFPGATimestamp() << ", ";

    for (auto &i : m_map)
    {
        m_file << i.second << ", ";
    }

    // Force output to disk
    m_file << endl;
    m_file.flush();
}