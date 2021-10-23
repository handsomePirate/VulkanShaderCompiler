#pragma once
#include <SoftwareCore/Singleton.hpp>
#include <SoftwareCore/Logger.hpp>

#define CompilerLogger ::Core::Singleton<::Core::Logger>::GetInstance()
