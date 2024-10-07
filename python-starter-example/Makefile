
# determine Python version, need at least 3.7
PYTHON=python3
ifneq (, $(shell which python3.7))
	PYTHON=python3.7
endif
ifneq (, $(shell which python3.8))
	PYTHON=python3.8
endif
ifneq (, $(shell which python3.9))
	PYTHON=python3.9
endif
ifneq (, $(shell which python3.10))
	PYTHON=python3.10
endif
ifneq (, $(shell which python3.11))
	PYTHON=python3.11
endif
ifneq (, $(shell which python3.12))
	PYTHON=python3.12
endif

test: product_test.py product.py
	${PYTHON} product_test.py

grade: grade.py product_test.py product.py
	${PYTHON} grade.py

clean:
	rm -f results.json
