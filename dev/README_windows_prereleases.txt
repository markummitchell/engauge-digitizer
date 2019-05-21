To access Windows pre-releases, when made available by the developers, follow these steps:

* Go go https://ci.appveyor.com/project/markummitchell/engauge-digitizer
* Click on either job 'Environment: ...BUILD_TYPE=X86...' or 'Environment: ...BUILD_TYPE=x64...'
  for a 32 or 64 bit pre-release, respectively. There should be a green bar at the beginning of
  the job line, which means the build was successfully completed
* Click on the Artifacts link on the right side
* Download the file 'engauge-build.7z' or 'engauge-build-x64.7z'
* Extract the file using a free 7z tool. For example:
  (Linux)   p7zip -d engauge-build-x64.7z
  (Windows) WinZip / (select engauge-build-x64.7z) / Unzip
* Go into the new directory and run engauge.exe

