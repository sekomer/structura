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
./dist.sh

check_error $? "Build failed"

# manylinux 
auditwheel repair dist/*.whl
check_error $? "auditwheel failed"

# upload if --upload is specified
if [ "$1" == "--upload" ]; then
    twine upload --verbose wheelhouse/*.whl
    check_error $? "Failed to upload package"
fi

# pip install locally
pip install dist/*cp38*.whl
check_error $? "Failed to run $file"

# run tests
for file in test/*.py; do
    python $file
    check_error $? "Failed to run $file"
done