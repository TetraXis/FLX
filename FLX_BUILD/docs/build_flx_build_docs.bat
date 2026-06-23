@echo off
setlocal

cd /d "%~dp0"

echo.
echo Building flx_build docs...

latexmk -pdf -auxdir=output -outdir=. flx_build.tex

if %errorlevel% neq 0 (
    echo.
    echo ERROR: Build failed
    pause
    exit /b %errorlevel%
)

if not exist "..\..\DOCS" mkdir "..\..\DOCS"

copy /Y "flx_build.pdf" "..\..\DOCS\flx_build.pdf"

echo.
echo PDF saved
pause