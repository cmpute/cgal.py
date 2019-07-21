import sys

try:
    from skbuild import setup
except ImportError:
    raise ImportError('scikit-build is required for installing')

setup(
    name="cgal-py",
    version="0.0.3",
    description="Cython bindings of Computational Geometry Algorithms Library (CGAL)",
    long_description='(see project homepage)',
    author='Jacob Zhong',
    author_email='cmpute@gmail.com',
    url='https://github.com/cmpute/cgal.py',
    download_url='https://github.com/cmpute/cgal.py/archive/master.zip',
    license='BSD-3-Clause',
    packages=['cgal'],
    package_data={'cgal':['*.pxd', '*/*.pxd', '__init__.pxd', '*.h']},
    install_requires=['numpy'],
    setup_requires=['pybind11', 'scikit-build'],
    extras_require={'test': ['pytest']},
    classifiers=[
        'Programming Language :: C++',
        'Programming Language :: Cython',
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: BSD License',
        'Operating System :: OS Independent',
        'Development Status :: 2 - Pre-Alpha',
        'Topic :: Scientific/Engineering'
    ],
    keywords=['cgal', 'geometry', 'algorithms', 'numpy', 'cython', 'binding'],
)
