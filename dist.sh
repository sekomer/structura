conda activate py36
sudo /home/selftech/miniconda3/envs/py36/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py36/bin/python setup.py bdist_wheel

conda activate py37
sudo /home/selftech/miniconda3/envs/py37/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py37/bin/python setup.py bdist_wheel

conda activate py38
sudo /home/selftech/miniconda3/envs/py38/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py38/bin/python setup.py bdist_wheel

conda activate py39
sudo /home/selftech/miniconda3/envs/py39/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py39/bin/python setup.py bdist_wheel

conda activate py310
sudo /home/selftech/miniconda3/envs/py310/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py310/bin/python setup.py bdist_wheel

conda activate py311
sudo /home/selftech/miniconda3/envs/py311/bin/python setup.py sdist
sudo /home/selftech/miniconda3/envs/py311/bin/python setup.py bdist_wheel
