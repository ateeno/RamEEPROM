#include <RamDisk.h>
#include <RamEEPROM.h>

RamEEPROM ram;
RamVolume vol;
RamFile file;
char buf[40];
//------------------------------------------------------------------------------
void setup() {
	Serial.begin(115200);

	Serial.print(F("Format (Y/N): "));
	while (!Serial.available())
		;
	char c = toupper(Serial.read());
	Serial.println(c);

	if (c == 'Y') {
		// use defaults:
		// totalBlocks: entire RAM
		// dirBlocks: 4  (64 entries)
		// clusterSizeBlocks: 1 (one 512 byte block per cluster)
		if (!vol.format(&ram)) {
			Serial.println(F("format failed"));
			return;
		}
	} else if (c != 'N') {
		Serial.println(F("Invalid entry"));
		return;
	}
	if (!vol.init(&ram)) {
		Serial.println(F("init fail"));
		return;
	}
	vol.printInfo(&Serial);

	if (!file.open("TEST.TXT", O_CREAT | O_RDWR | O_TRUNC)) {
		Serial.println(F("open fail"));
		return;
	}
	file.println("Hello RamDisk!");
	file.println("Line to test fgets");
	file.rewind();
	int lineNumber = 0;

	Serial.println(">>>");
	// Read file line at a time.
	while (file.fgets(buf, sizeof(buf)) > 0) {
		Serial.print(++lineNumber);
		Serial.print(F(": "));
		Serial.print(buf);
	}
	file.close();
	Serial.println("<<<");
	Serial.println();
	Serial.println("-------------------------------------------");
	vol.ls(&Serial, LS_DATE | LS_R | LS_SIZE);
	Serial.println("-------------------------------------------");
	Serial.println();
	Serial.println(F("Done!"));
}
//------------------------------------------------------------------------------
void loop() {

}
