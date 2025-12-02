@echo off
REM Quick fix for port names in Routes.txt
REM Replace HongKong -> Hong Kong, etc.

setlocal enabledelayedexpansion

cd public

REM Use PowerShell to fix the file
powershell -Command "^
  $content = Get-Content Routes.txt -Raw; ^
  $content = $content -replace 'HongKong', 'Hong Kong'; ^
  $content = $content -replace 'CapeTown', 'Cape Town'; ^
  $content = $content -replace 'PortLouis', 'Port Louis'; ^
  $content = $content -replace 'AbuDhabi', 'Abu Dhabi'; ^
  $content = $content -replace 'NewYork', 'New York'; ^
  $content = $content -replace 'LosAngeles', 'Los Angeles'; ^
  $content = $content -replace 'Dublin', 'Dublin'; ^
  Set-Content Routes.txt $content; ^
  Write-Host 'Routes.txt fixed successfully'
"
