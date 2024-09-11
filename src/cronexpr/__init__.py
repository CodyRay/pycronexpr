import _ccronexpr
from datetime import datetime, timezone

def next_fire(cron: str, date: datetime=None):
    if cron is None:
        raise ValueError("cron expression is required")
    
    if date is None:
        now = datetime.now()
    elif not isinstance(date, datetime):
        raise ValueError("date must be a datetime object")
    else:
        now = datetime.fromtimestamp(date.timestamp())
    return _ccronexpr.cron_next(cron, now).astimezone(timezone.utc)

def prev_fire(cron: str, date: datetime=None):
    if cron is None:
        raise ValueError("cron expression is required")
    
    if date is None:
        now = datetime.now()
    elif not isinstance(date, datetime):
        raise ValueError("date must be a datetime object")
    else:
        now = datetime.fromtimestamp(date.timestamp())
    return _ccronexpr.cron_prev(cron, now).astimezone(timezone.utc)