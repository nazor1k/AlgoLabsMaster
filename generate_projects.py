"""
Генератор Visual Studio 2022 проектів для лабораторних робіт №5..№15.

Створює:
  All_AlGO_LABS/
    AlgoLabsMaster.sln
    Lab5/
      Lab5.vcxproj
      Lab5.vcxproj.filters
      main.cpp   (плейсхолдер — не перезаписується, якщо вже існує)
    Lab6/
      ...
    ...
    Lab15/

Запускати з будь-якої директорії — шляхи рахуються відносно файлу скрипта.
Повторний запуск безпечний: існуючі main.cpp не чіпаємо, .vcxproj/.sln
регенеруються (GUID'и стабільні — беруться з uuid5 за назвою проекту).
"""

import os
import uuid

ROOT = os.path.dirname(os.path.abspath(__file__))
LABS = list(range(5, 16))  # Lab5..Lab15

# Стабільний namespace для генерації GUID'ів, щоб повторні запуски
# не ламали існуючий .sln.
NS = uuid.UUID("6ba7b810-9dad-11d1-80b4-00c04fd430c8")
CPP_TYPE_GUID = "{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}"  # VC++ project type


def proj_guid(name: str) -> str:
    return "{" + str(uuid.uuid5(NS, name)).upper() + "}"


VCXPROJ_TEMPLATE = r"""<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Win32">
      <Configuration>Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Win32">
      <Configuration>Release</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Debug|x64">
      <Configuration>Debug</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|x64">
      <Configuration>Release</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <VCProjectVersion>17.0</VCProjectVersion>
    <Keyword>Win32Proj</Keyword>
    <ProjectGuid>__GUID__</ProjectGuid>
    <RootNamespace>__NAME__</RootNamespace>
    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings" />
  <ImportGroup Label="Shared" />
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <LanguageStandard>stdcpp17</LanguageStandard>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>WIN32;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <LanguageStandard>stdcpp17</LanguageStandard>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <LanguageStandard>stdcpp17</LanguageStandard>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <LanguageStandard>stdcpp17</LanguageStandard>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ClCompile Include="main.cpp" />
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets" />
</Project>
"""

FILTERS_TEMPLATE = r"""<?xml version="1.0" encoding="utf-8"?>
<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup>
    <Filter Include="Source Files">
      <UniqueIdentifier>{4FC737F1-C7A5-4376-A066-2A32D752A2FF}</UniqueIdentifier>
      <Extensions>cpp;c;cc;cxx;c++;cppm;ixx;def;odl;idl;hpj;bat;asm;asmx</Extensions>
    </Filter>
  </ItemGroup>
  <ItemGroup>
    <ClCompile Include="main.cpp">
      <Filter>Source Files</Filter>
    </ClCompile>
  </ItemGroup>
</Project>
"""

PLACEHOLDER_CPP = """// {name}/main.cpp
// Лабораторна робота №{n}. Заглушка — буде замінена кодом.

#include <iostream>
#include <windows.h>

int main() {{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::cout << "Lab {n}: TODO" << std::endl;
    return 0;
}}
"""


def write_project(n: int):
    name = f"Lab{n}"
    proj_dir = os.path.join(ROOT, name)
    os.makedirs(proj_dir, exist_ok=True)

    guid = proj_guid(name)

    vcxproj = VCXPROJ_TEMPLATE.replace("__GUID__", guid).replace("__NAME__", name)
    with open(os.path.join(proj_dir, f"{name}.vcxproj"), "w", encoding="utf-8") as f:
        f.write(vcxproj)

    with open(os.path.join(proj_dir, f"{name}.vcxproj.filters"), "w", encoding="utf-8") as f:
        f.write(FILTERS_TEMPLATE)

    main_path = os.path.join(proj_dir, "main.cpp")
    if not os.path.exists(main_path):
        with open(main_path, "w", encoding="utf-8") as f:
            f.write(PLACEHOLDER_CPP.format(name=name, n=n))

    return name, guid


def write_solution(projects):
    """projects: list of (name, guid)"""
    lines = []
    lines.append("")
    lines.append("Microsoft Visual Studio Solution File, Format Version 12.00")
    lines.append("# Visual Studio Version 17")
    lines.append("VisualStudioVersion = 17.0.0.0")
    lines.append("MinimumVisualStudioVersion = 10.0.40219.1")

    for name, guid in projects:
        rel = f"{name}\\{name}.vcxproj"
        lines.append(
            f'Project("{CPP_TYPE_GUID}") = "{name}", "{rel}", "{guid}"'
        )
        lines.append("EndProject")

    lines.append("Global")
    lines.append("\tGlobalSection(SolutionConfigurationPlatforms) = preSolution")
    for cfg in ("Debug|Win32", "Debug|x64", "Release|Win32", "Release|x64"):
        lines.append(f"\t\t{cfg} = {cfg}")
    lines.append("\tEndGlobalSection")

    lines.append("\tGlobalSection(ProjectConfigurationPlatforms) = postSolution")
    for name, guid in projects:
        for cfg in ("Debug|Win32", "Debug|x64", "Release|Win32", "Release|x64"):
            lines.append(f"\t\t{guid}.{cfg}.ActiveCfg = {cfg}")
            lines.append(f"\t\t{guid}.{cfg}.Build.0 = {cfg}")
    lines.append("\tEndGlobalSection")

    lines.append("\tGlobalSection(SolutionProperties) = preSolution")
    lines.append("\t\tHideSolutionNode = FALSE")
    lines.append("\tEndGlobalSection")

    sol_guid = "{" + str(uuid.uuid5(NS, "AlgoLabsMaster.sln")).upper() + "}"
    lines.append("\tGlobalSection(ExtensibilityGlobals) = postSolution")
    lines.append(f"\t\tSolutionGuid = {sol_guid}")
    lines.append("\tEndGlobalSection")
    lines.append("EndGlobal")
    lines.append("")

    sln_path = os.path.join(ROOT, "AlgoLabsMaster.sln")
    with open(sln_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))


def main():
    created = []
    for n in LABS:
        created.append(write_project(n))
    write_solution(created)
    print(f"OK: {len(created)} projects + AlgoLabsMaster.sln in {ROOT}")


if __name__ == "__main__":
    main()
