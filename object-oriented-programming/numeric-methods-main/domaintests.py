from numericmethods import NumericMethods
from exceptions import ZerosAreNotGuaranteed, FunctionDerivativeIsVeryCloseToZero, SecantMethodIsDivergent
import pytest

# BISECTION METHOD:

def test_bisection_method():
    interval = [-1, 5]
    error = 10**-10
    it_max = 200
    polynomial = [13, 91, -5]
    
    bisection = NumericMethods(polynomial, interval, error, it_max)
    bisection.bisection_method()

    assert bisection.it_max == 36

def test_bisection_method_exception():
    interval = [1, 4]
    error = 10**-10
    it_max = 200
    polynomial = [13, 91, -5]

    bisection = NumericMethods(polynomial, interval, error, it_max)

    with pytest.raises(ZerosAreNotGuaranteed):
        bisection.bisection_method()

# NEWTON METHOD: 

def test_newton_method():
    interval = 10
    error = 10**-8
    it_max = 200
    polynomial = [13, 91, -5]

    newton = NumericMethods(polynomial, interval, error, it_max)
    newton.newton_method()

    assert newton.it_max == 6

def test_newton_method_exception():
    position_x0 = -3.5
    error = 10**-8
    it_max = 200
    polynomial = [13, 91, -5]
    
    newton = NumericMethods(polynomial, position_x0, error, it_max)

    with pytest.raises(FunctionDerivativeIsVeryCloseToZero):
        newton.newton_method()

# SECANT METHOD:

def test_secant_method():
    interval = [52, 58]
    error = 10**-6
    it_max = 200
    polynomial = [13, 91, -5]

    secant = NumericMethods(polynomial, interval, error, it_max)
    secant.secant_method()

    assert secant.it_max == 11

def test_secant_method_exception():
    interval = [13, 13]
    error = 10**-6
    it_max = 200
    polynomial = [13, 91, -5]
    
    secant = NumericMethods(polynomial, interval, error, it_max)
    
    with pytest.raises(SecantMethodIsDivergent):
        secant.secant_method()