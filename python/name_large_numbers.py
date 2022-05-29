import random # Only needed for generate_numerical_string().

digits = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine', ]
teens = ['ten', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen', ]
tens = ['zero', 'one', 'twenty', 'thirty', 'fourty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety', ]
digit_prefixes = ['', 'un', 'duo', 'tres', 'quattuor', 'quin', 'ses', 'sept', 'octo', 'noven', ]
small_base = ['', 'million', 'billion', 'trillion', 'quadrillion', 'quintillion', 'sextillion', 'septillion', 'octillion', 'nonillion', ]
tens_base = ['', 'thousand', 'million', 'billion', 'trillion', 'quadrillion', 'quintillion', 'sextillion', 'septillion', 'octillion', 'nonillion', 'decillion', ]
teens_base = ['', 'decillion', 'vigintillion', 'trigintillion', 'quadragintillion', 'quinquagintillion', 'sexagintillion', 'septuagintillion', 'octogintillion', 'nonagintillion', ]

def generate_numerical_string(num_digits):
    '''
    Generates a numerical string of the specified length or less.

    Parameters:
        num_digits (integer): The length of the desired numerical string.

    Returns:
        num_string: A string made from random digits.
    '''

    if not isinstance(num_digits, int):
        raise Exception('Must provide a number.')

    if num_digits < 0:
        raise Exception('Number must be positive.')

    num_string = ''
    for _ in range(num_digits):
        num_string += str(random.randint(0, 9))
    num_string = num_string.lstrip('0')
    return num_string


def group_into_triples(num_string):
    '''
    Turns a numerical string into an array of three digit groups.
    Ex: '1234' -> [(0, 0, 1), (2, 3, 4)]

    Parameters:
        num_string (string): A string of digits.

    Returns:
        groups: An array of groups that represent the digits of the input string.
    '''

    if not isinstance(num_string, str):
        raise Exception('Must provide a string.')

    if not num_string.isdigit():
        raise Exception('String must be made of digits.')

    # Pad the string so that its length is a multiple of three.
    n = num_string
    padding = -len(n) % 3
    n = '0'*padding+n

    # Populate the groups.
    groups = []
    for j in range(int(len(n)/3)):
        groups.append((
            int(n[j*3+0]),
            int(n[j*3+1]),
            int(n[j*3+2])
        ))
    return groups


def print_with_separators(num_string, separator=','):
    '''
    Prints a number with separators to make human comprehension easier.
    Ex: '3000' -> '3,000'

    Parameters:
        num_string: A string of digits.
        separator: The symbol to use to separate groupings.

    Returns:
        None
    '''

    if not isinstance(num_string, str):
        raise Exception('Must provide a string.')

    if not isinstance(separator, str):
        raise Exception('Separator must be a string.')

    if not num_string.isdigit():
        raise Exception('String must be made of digits.')

    groups = group_into_triples(num_string)

    l = []
    first = True
    for group in groups:
        group = [str(x) for x in group]
        s = ''.join(group)
        if first:
            s = s.lstrip('0')
            first = False
        l.append(s)
    print(separator.join(l))


def triple_name(triple):
    '''
    Returns the English representation of the three digit 'triple'.
    Ex: [1, 2, 3] -> 'one hundred twenty three'

    Parameters:
        triple: An array of three digits.

    Returns:
        triple_string: A string representation of the provided number.
    '''

    triple_string = ''

    if triple[0] != 0:
        triple_string += '%s hundred ' % (digits[triple[0]])

    if triple[1] == 1:
        triple_string += '%s ' % (teens[triple[2]])
    else:
        if triple[1] != 0:
            triple_string += '%s ' % (tens[triple[1]])

        if triple[2] != 0:
            triple_string += '%s ' % (digits[triple[2]])

    return triple_string


def base_from_index(order):
    '''
    Returns a string representing the base of a specified order.
    Ex: 2 -> 'million', 3-> 'billion'

    Parameters:
        order: The desired 'order' or 'base' of the number.

    Returns:
        order_string: A string that represents the specified base.
    '''

    if not isinstance(order, int):
        raise Exception('Must provide a number.')

    if order < 0:
        raise Exception('Number must be positive.')

    if order > 100:
        raise Exception('Number is too large.')

    n = order

    # Special case.
    if n == 0:
        return 'thousand'

    # Special case.
    if n == 100:
        return 'centillion'

    # Special case.
    if n < 10:
        return small_base[n]

    n = [x for x in str(n)]
    order_string = ''
    order_string += digit_prefixes[int(n[-1])]
    if len(n) > 1:
        order_string += teens_base[int(n[-2])]
    return order_string


def representation_of_number(num_string):
    '''
    Return the English representation of a string of digits.
    Ex: '12341234' -> 'twelve million, three hundred fourty one thousand, two
    hundred thirty four'

    Parameters:
        num_string: A string of digits.

    Returns:
        num_text: The English representation of the input number.
    '''

    if not isinstance(num_string, str):
        raise Exception('Must provide a string.')

    if not num_string.isdigit():
        raise Exception('String must be made of digits.')

    n = num_string
    n = n.lstrip('0')
    if len(n) > 306:
        raise Exception('Number is too large.')

    # Special case.
    if n == '':
        return 'zero'

    groups = group_into_triples(n)

    num_text = ''
    for index, group in enumerate(groups):

        # Skip '000' cases.
        if group[0] == 0 and group[1] == 0 and group[2] == 0:
            continue

        # Combine the triple name and the string representation of the order.
        order = len(groups)-index-1
        num_text += triple_name(group)
        if order != 0:
            num_text += base_from_index(order-1)+', '

    # Trim excess spaces and punctuation.
    num_text = num_text.rstrip(' ')
    num_text = num_text.rstrip(',')
    return num_text

if __name__ == "__main__":
    n = generate_numerical_string(306)
    print_with_separators(n)
    print(representation_of_number(n))
