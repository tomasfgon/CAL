cmake_minimum_required(VERSION 3.15)
project(Projeto)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32 wsock32)

add_executable(Projeto main.cpp src/PontoRecolha.cpp src/Coordenadas.h src/TipoLixo.h src/PontoRecolhaDomiciliario.h)