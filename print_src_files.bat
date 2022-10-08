@echo off
:: i need to make this smarter, this sucks ass
for %%f in (.\basic_renderer\src\*.cpp) do echo %%f
for %%f in (.\basic_renderer\vendor\stb_image\*.cpp) do echo %%f
for %%f in (.\basic_renderer\vendor\loga\*.cpp) do echo %%f
for %%f in (.\basic_renderer\vendor\imgui\*.cpp) do echo %%f
for %%f in (.\basic_renderer\src\tests\*.cpp) do echo %%f
