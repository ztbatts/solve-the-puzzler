# solve-the-puzzler
Tools to solve NPR Weekend Edition puzzler
E.g. https://www.npr.org/2020/12/20/948348016/sunday-puzzle-christmas-capitals 

## Instructions (Command-Line)
1. Install git lfs (```git lfs install```). This makes version control for certain datasets easier.
1. Install pipenv (```sudo apt install pipenv```). 
2. Spin up a virtual environment (```pipenv shell; pipenv install```)
3. Create and move to build folder (```mkdir build/; cd build/```)
4. Run cmake from the build folder, need to specify build type (```cmake .. -DCMAKE_BUILD_TYPE=Debug```)
   This should automatically fetch conan packages. If it doesn't work, trying manually fetching first (```conan install ..```)
5. Build (```cmake --build . ```)
6. Run the appropriate executable (e.g. ```./bin/BuenosAires```)

## Known issues
* Conan version must be > 1.23, otherwise you may experience a cmake error similar to https://github.com/conan-io/conan-center-index/issues/2807
* range-v3/0.11.0 breaks things ... haven't tried it yet
