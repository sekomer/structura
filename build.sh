sudo -v

function check_error {
    if [ $1 -ne 0 ]; then
        echo "Error: $2"
        sudo kill -9 $$
    fi
}

# clean up
sudo rm -rf dist wheelhouse
check_error $? "Cleanup failed"

# uninstall current version
pip uninstall -y structura

# build
sudo /home/selftech/miniconda3/envs/py35/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py35/bin/python setup.py bdist_wheel
check_error $? "Build 35 failed"

sudo /home/selftech/miniconda3/envs/py36/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py36/bin/python setup.py bdist_wheel
check_error $? "Build 36 failed"

sudo /home/selftech/miniconda3/envs/py37/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py37/bin/python setup.py bdist_wheel
check_error $? "Build 37 failed"

sudo /home/selftech/miniconda3/envs/py38/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py38/bin/python setup.py bdist_wheel
check_error $? "Build 38 failed"

sudo /home/selftech/miniconda3/envs/py39/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py39/bin/python setup.py bdist_wheel
check_error $? "Build 39 failed"

sudo /home/selftech/miniconda3/envs/py310/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py310/bin/python setup.py bdist_wheel
check_error $? "Build 310 failed"

sudo /home/selftech/miniconda3/envs/py311/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py311/bin/python setup.py bdist_wheel
check_error $? "Build 311 failed"


# manylinux 
auditwheel repair dist/*.whl
check_error $? "auditwheel failed"

# upload if --upload is specified
if [ "$1" == "--upload" ]; then
    twine upload --verbose wheelhouse/*.whl
    check_error $? "Failed to upload package"
fi

# pip install locally
pip install wheelhouse/*cp38*.whl
check_error $? "Failed to run $file"

# run tests
for file in test/*.py; do
    python $file
    check_error $? "Failed to run $file"
done
