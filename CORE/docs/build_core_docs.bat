@echo off
setlocal

cd /d "%~dp0"

echo.
echo Building flx_core docs...

latexmk -pdf -auxdir=output -outdir=. flx_core.tex

if %errorlevel% neq 0 (
    echo.
    echo ERROR: Build failed
    pause
    exit /b %errorlevel%
)

if not exist "..\..\DOCS" mkdir "..\..\DOCS"

copy /Y "flx_core.pdf" "..\..\DOCS\flx_core.pdf"

echo.
echo PDF saved
pause