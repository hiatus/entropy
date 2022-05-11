TARGET := entropy

SRCDIR := src
OBJDIR := obj
INCDIR := $(SRCDIR)/include

HEADER := $(INCDIR)/shannon.h
SOURCE := $(SRCDIR)/main.c $(SRCDIR)/shannon.c

CWARNS := -Wall
CFLAGS := -std=gnu99 -I$(INCDIR)

OBJECT := $(addprefix $(OBJDIR)/, main.o shannon.o)


$(TARGET): $(OBJECT)
	@echo [$(CC)] $@
	@$(CC) -s -o $@ $(OBJECT) -lm

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	@echo [$(CC)] $@
	@$(CC) $(CWARNS) $(CFLAGS) -O2 -c -o $@ $<

$(OBJDIR)/shannon.o: $(SRCDIR)/shannon.c $(INCDIR)/shannon.h
	@echo [$(CC)] $@
	@$(CC) $(CWARNS) $(CFLAGS) -O3 -ffast-math -c -o $@ $<

$(OBJDIR):
	@mkdir $(OBJDIR)

$(OBJECT): | $(OBJDIR)

clean:
	@echo [rm] $(TARGET) $(OBJDIR)
	@rm -rf $(TARGET) $(OBJDIR) || true
