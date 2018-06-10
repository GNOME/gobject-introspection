all: _build

_build: Makefile *.rst tools/*.rst images/*.svg annotations/*.rst conf.py
	python3 -m sphinx  -b html . _build

linkcheck:
	python3 -m sphinx  -b linkcheck -n . _build

clean:
	rm -Rf _build
