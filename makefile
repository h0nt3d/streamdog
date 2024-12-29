SRC_DIR = src
BUILD_DIR = build

all : $(BUILD_DIR)/streamdog

$(BUILD_DIR)/streamdog: $(SRC_DIR)/streamdog.c
	mkdir -p $(BUILD_DIR)
	gcc $(SRC_DIR)/streamdog.c -o $(BUILD_DIR)/streamdog

install :
	install -Dm755 $(BUILD_DIR)/streamdog /usr/bin/streamdog
	install -Dm644 $(SRC_DIR)/streamdog.service /lib/systemd/system/streamdog.service
	systemctl daemon-reload

uninstall :
	rm -f /usr/bin/streamdog
	rm -f /lib/systemd/system/streamdog.service
	systemctl daemon-reload

clean:
	rm -rf $(BUILD_DIR)


