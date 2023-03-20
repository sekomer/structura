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
sudo python setup.py sdist
sudo python setup.py bdist_wheel

# sudo python3 -m build --sdist 
# sudo python3 -m build --wheel 

check_error $? "Build failed"

# manylinux 
auditwheel repair dist/*.whl
check_error $? "auditwheel failed"

# remove wheel other than manylinux
# sudo rm dist/*.whl
check_error $? "Failed to remove wheel"

# copy manylinux to dist
# sudo cp wheelhouse/*.whl dist/
check_error $? "Failed to copy manylinux to dist"

# remove wheelhouse
# sudo rm -rf wheelhouse
check_error $? "Failed to remove wheelhouse"

# upload if --upload is specified
if [ "$1" == "--upload" ]; then
    twine upload --verbose dist/*
    check_error $? "Failed to upload package"
fi

# pip install locally
pip install dist/*.whl
check_error $? "Failed to run $file"

# run tests
for file in test/*.py; do
    python $file
    check_error $? "Failed to run $file"
done