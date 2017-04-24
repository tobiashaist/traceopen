OBJS := test_0001.o ../element.o ../parameter.o ../light.o ../surface.o ../surfacespherical.o ../refraction.o ../refractionrays.o ../interaction.o ../tracing.o ../refractionwaves.o ../ray.o ../opticalsystem.o ../elementwithsurfaces.o ../wave.o ../point.o ../direction.o ../material.o ../jonesmatrix.o ../logging.o ../materialideal.o ../enviroment.o totest.o

# link
proggie: $(OBJS)
	g++ -g $(OBJS) -o test_0001

CFLAGS := -g





# pull in dependency info for *existing* .o files
-include $(OBJS:.o=.d)

# compile and generate dependency info;
# more complicated dependency computation, so all prereqs listed
# will also become command-less, prereq-less targets
#   sed:    strip the target (everything before colon)
#   sed:    remove any continuation backslashes
#   fmt -1: list words one per line
#   sed:    strip leading spaces
#   sed:    add trailing colons
%.o: %.cc
	g++ -c $(CFLAGS) $*.cc -o $*.o
	g++ -MM $(CFLAGS) $*.cc > $*.d
	@cp -f $*.d $*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

# remove compilation products
clean:
	rm -f proggie *.o *.d
