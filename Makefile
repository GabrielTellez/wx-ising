WXCCFLAGS=`wx-config --cflags`
WXLIBS=`wx-config --libs`
CXXFLAGS=$(WXCCFLAGS) -Wall
monte-carlo: monte-carlo.cpp monte-carlo.hh basic-lattice.cc basic-lattice.hh spin.hh spin.cc wx-spin.cc wx-spin.hh wx-lattice.cc wx-lattice.hh wx-table-sizer.cc wx-table-sizer.hh bitmaps/start.xpm bitmaps/stop.xpm bitmaps/fast.xpm bitmaps/slow.xpm bitmaps/spinup.xpm bitmaps/spindown.xpm monte-carlo-preferences.h extra-widgets.hh extra-widgets.cc curves_wx.hh curves_wx.cc status-button.hh status-button.cc metropolis.cc metropolis.hh dialogs.hh dialogs.cc log-status.cc log-status.hh
	$(CXX) $(CXXFLAGS) $(WXLIBS) monte-carlo.cpp -o monte-carlo
try-metropolis: try-metropolis.cc try-metropolis.hh wx-spin.cc wx-spin.hh spin.cc spin.hh basic-lattice.cc basic-lattice.hh wx-lattice.cc wx-lattice.hh metropolis.cc metropolis.hh choice.hh choice.cc
	c++ try-metropolis.cc  -o try-metropolis `wx-config --cflags --libs` 
try: try.cc try.hh wx-spin.cc wx-spin.hh spin.cc spin.hh basic-lattice.cc basic-lattice.hh wx-lattice.cc wx-lattice.hh
	c++ try.cc  -o try `wx-config --cflags --libs` 
spin.o: spin.hh spin.cc
basic-lattice.o: basic-lattice.hh basic-lattice.cc
wx-spin.o: wx-spin.hh wx-spin.cc spin.cc spin.hh
	c++ wx-spin.cc -c -o wx-spin.o $(WXCCFLAGS)
try.o: try.cc try.hh wx-spin.cc wx-spin.hh spin.cc spin.hh basic-lattice.cc basic-lattice.hh
	c++ -c try.cc -o try.o $(WXCCFLAGS) 
metropolis.o: metropolis.cc metropolis.hh basic-lattice.cc basic-lattice.hh spin.hh spin.cc



