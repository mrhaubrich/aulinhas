import pandas as pd
from mage_ai.data_cleaner.transformer_actions.base import BaseAction
from mage_ai.data_cleaner.transformer_actions.constants import ActionType, Axis
from mage_ai.data_cleaner.transformer_actions.utils import build_transformer_action

if 'transformer' not in globals():
    from mage_ai.data_preparation.decorators import transformer
if 'test' not in globals():
    from mage_ai.data_preparation.decorators import test


@transformer
def transform_df(df1, df2, **kwargs) -> pd.DataFrame:
    """
    the following movies and directors csv were loaded:
    directors.csv:
    directorID,directorName

    movies.csv:
    movieID;title;releaseYear;url;directorID

    df1 and df2 is already loaded with the data from the csv files as a pandas dataframe.
    """
    return df1.merge(df2, on='directorID', how='inner')
    


@test
def test_output(output, *args) -> None:
    """
    Template code for testing the output of the block.
    """
    assert output is not None, 'The output is undefined'