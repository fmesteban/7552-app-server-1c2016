# 7552-app-server-1c2016
App server del tp de taller2 1c2016

Master
[![Build Status](https://travis-ci.org/fmesteban/7552-app-server-1c2016.svg?branch=master)](https://travis-ci.org/fmesteban/7552-app-server-1c2016)
[![codecov.io](https://codecov.io/github/fmesteban/7552-app-server-1c2016/coverage.svg?branch=master)](https://codecov.io/github/fmesteban/7552-app-server-1c2016?branch=master)

###Git Pre Commit Hook
Se puede modificar el [pre-commit.sh](pre-commit.sh) script para que haga lo que se desee.
Para linkear el hook:

  ```bash
    > chmod +x pre-commit.sh
    > ln -s ../../pre-commit.sh .git/hooks/pre-commit
  ```

Por ahora, el mismo correra cpplint a todo el src de la aplicacion. De encontrar errores, no dejará hacer commit. Para forzar el commit se debe agregar `--no-verify` al `git commit`.


###Herramientas Necesarias


###How to Build


###How to Run


###How to Run Tests
