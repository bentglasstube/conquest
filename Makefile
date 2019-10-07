UNAME=$(shell uname)

SOURCES=$(wildcard *.cc) $(wildcard gam/*.cc)
CONTENT=$(wildcard content/*.png) $(wildcard content/*.ogg) $(wildcard content/*.wav)
BUILDDIR=output
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))
NAME=conquest
APP_NAME="CONQuest"

CC=$(CROSS)g++
LD=$(CROSS)ld
AR=$(CROSS)ar
PKG_CONFIG=$(CROSS)pkg-config
CFLAGS=-O3 --std=c++14 -Wall -Wextra -Werror -pedantic -I gam -DNDEBUG

ifeq ($(UNAME), Linux)
	PACKAGE=$(NAME)-linux.tgz
	LDFLAGS=-static-libstdc++ -static-libgcc
	LDLIBS=`$(PKG_CONFIG) sdl2 SDL2_mixer SDL2_image SDL2_ttf --cflags --libs` -L/home/alan/source/gam -Wl,-Bstatic -lgam
endif
ifeq ($(UNAME), Darwin)
	PACKAGE=$(NAME)-osx.tgz
	LDLIBS=-framework SDL2 -framework SDL2_mixer -framework SDL2_image SDL2_ttf -rpath @executable_path/../Frameworks
	CFLAGS+=-mmacosx-version-min=10.9
endif

EXECUTABLE=$(BUILDDIR)/$(NAME)

all: $(EXECUTABLE)

echo:
	@echo "Content: $(CONTENT)"
	@echo "Sources: $(SOURCES)"
	@echo "Uname: $(UNAME)"
	@echo "Package: $(PACKAGE)"

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(BUILDDIR)/gam
	$(CC) -c $(CFLAGS) -o $@ $<

package: $(PACKAGE)

$(NAME)-linux.tgz: $(EXECUTABLE)
	mkdir -p $(NAME)/content
	cp $(EXECUTABLE) $(NAME)
	cp $(CONTENT) $(NAME)/content/.
	tar zcf $@ $(NAME)
	rm -rf $(NAME)

$(NAME)-osx.tgz: $(APP_NAME).app
	mkdir $(NAME)
	cp -r $(APP_NAME).app $(NAME)/.
	tar zcf $@ $(NAME)
	rm -rf $(NAME)

$(NAME)-windows.zip: $(EXECUTABLE)
	mkdir $(NAME)
	cp $(EXECUTABLE) $(NAME)/`basename $(EXECUTABLE)`.exe
	cp -R content $(NAME)/content
	# TODO set up dlls and shit
	zip -r $@ $(NAME)
	rm -rf $(NAME)

$(APP_NAME).app: $(EXECUTABLE) launcher $(CONTENT) Info.plist
	rm -rf $(APP_NAME).app
	mkdir -p $(APP_NAME).app/Contents/{MacOS,Frameworks}
	cp $(EXECUTABLE) $(APP_NAME).app/Contents/MacOS/game
	cp launcher $(APP_NAME).app/Contents/MacOS/launcher
	cp -R content $(APP_NAME).app/Contents/MacOS/content
	cp Info.plist $(APP_NAME).app/Contents/Info.plist
	cp -R /Library/Frameworks/SDL2.framework $(APP_NAME).app/Contents/Frameworks/SDL2.framework
	cp -R /Library/Frameworks/SDL2_mixer.framework $(APP_NAME).app/Contents/Frameworks/SDL2_mixer.framework
	cp -R /Library/Frameworks/SDL2_image.framework $(APP_NAME).app/Contents/Frameworks/SDL2_image.framework

clean:
	rm -rf $(BUILDDIR) $(APP_NAME).app $(PACKAGE)

.PHONY: all clean run package
