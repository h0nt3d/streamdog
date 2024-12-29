SRC_DIR = src
BUILD_DIR = build

all : $(BUILD_DIR)/streamdog

$(BUILD_DIR)/streamdog: $(SRC_DIR)/streamdog.c
	mkdir -p $(BUILD_DIR)
	gcc -o $(SRC_DIR)/streamdog.c -o $(BUILD_DIR)/streamdog

install :
	install -Dm755 $(BUILD_DIR)/streamdog /usr/bin/streamdog
	install -Dm644 streamdog.service /lib/systemd/system/streamdog.service
	systemctl daemon-reload

uninstall :
	rm -f /usr/bin/my-daemon
	rm -f /lib/systemd/system/my-daemon.service
	systemctl daemon-reload

clean:
	rm -rf $(BUILD_DIR)


