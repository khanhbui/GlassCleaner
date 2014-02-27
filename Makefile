keystore:
	keytool -genkey -v -keyalg RSA -keystore build/GlassCleaner.keystore -alias GlassCleaner -validity 10000

sign:
	jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore build/GlassCleaner.keystore build/GlassCleaner_unsigned.apk GlassCleaner

verify:
	jarsigner -verify -verbose -certs build/GlassCleaner_unsigned.apk

zalign:
	zipalign -f -v 4 build/GlassCleaner_unsigned.apk build/GlassCleaner.apk

all:
	make sign
	make verify
	make zalign
