cmake_minimum_required(VERSION 3.31)

project(CalculadoraInvestimentoArqUnico VERSION 1.0.0 LANGUAGES CXX)

# Configuração C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---> ATIVE AUTOMOC E AUTORCC GLOBALMENTE <---
set(CMAKE_AUTOMOC ON)      # Necessário para sinais/slots do Qt
set(CMAKE_AUTORCC ON)      # ESSENCIAL para compilar resources.qrc (Imagens)

# Encontrar Qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Se Qt6 não for encontrado, tenta Qt5
if(NOT Qt6_FOUND)
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
endif()

# Definir fonte dos arquivos
set(SOURCES
        main.cpp
)

# Define resources explicitly - Obrigatório para Imagens
qt_add_resources(RESOURCE_FILES
        resources.qrc
)

# Criar executável
add_executable(CalculadoraInvestimentoArqUnico
        ${SOURCES}
        ${RESOURCE_FILES} #Obrigatório para Imagens
)

# Linking das bibliotecas Qt
if(Qt6_FOUND)
    target_link_libraries(CalculadoraInvestimentoArqUnico Qt6::Core Qt6::Widgets)
else()
    target_link_libraries(CalculadoraInvestimentoArqUnico Qt5::Core Qt5::Widgets)
endif()

# Configurações adicionais para Windows
if(WIN32)
    set_target_properties(CalculadoraInvestimentoArqUnico PROPERTIES
            WIN32_EXECUTABLE ON
    )
endif()