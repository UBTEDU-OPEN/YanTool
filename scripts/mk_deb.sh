#!/bin/bash
version=$2
release_date=`date "+%Y%m%d"`
package_size=0
out_put_file_name="UBT-Yanshee-Yantool-v${version}_${release_date}.deb"
if [ -d tmp ]; then
    rm -rf tmp
fi
mkdir tmp

cp --parent -a -r -t ./tmp /opt/yantool/
cp --parent -a -r -t ./tmp /home/pi/Desktop/yantool.desktop

package_size=`du -sh tmp | awk '{print $1}'`
cp -arf DEBIAN ./tmp
touch ./tmp/DEBIAN/control
(echo "Package: UBT-Yanshee-Yantool"
 echo "Version: $version" 
 echo "Section: Education"
 echo "Priority: required" 
 echo "Depends:" 
 echo "Suggests:" 
 echo "Architecture: armhf" 
 echo "Installed-Size: $package_size" 
 echo "Maintainer: ubtedu" 
 echo "Provides: ubt" 
 echo "Description: Yanshee Device Management Tool." ) > tmp/DEBIAN/control

echo "The generated deb file will be $out_put_file_name"

dpkg-deb -b tmp $out_put_file_name

rm -rf tmp
