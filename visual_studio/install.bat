mkdir "%ProgramW6432%"\data_transmission

copy Release\data_transmission.lib "%ProgramW6432%"\data_transmission

mkdir "%ProgramW6432%"\data_transmission\include\data_transmission
xcopy /f /y ..\src\data_transmission\include\data_transmission\data_transmission.h ^
  "%ProgramW6432%"\data_transmission\include\data_transmission
